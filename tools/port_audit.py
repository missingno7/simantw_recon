"""Cross-version port audit: which Win16 game functions carry Windows-specific behaviour.

    python tools/port_audit.py [--json build/port/audit.json] [--md build/port/audit.md]

Mission (2026-09-30): the DOS reconstruction (D:\\Prog\\simant_recon, read-only) is the behavioural
authority for a portable SDL3 port. This project only recovers the Windows-specific delta. For every GAME
function this tool records:
  - the Windows imports it calls directly (USER / GDI / KERNEL / MMSYSTEM / ...), resolved to names;
  - its DOS counterpart, if the DOS project pairs one (any confidence), and whether that DOS function is exact;
  - whether it is admitted here, and its current opcode ratio;
  - call-graph facts: callers, callees, and the distance to the nearest Windows API caller;
and proposes a mission class:
  SHARED_WITH_DOS_IGNORE            paired with DOS and no direct Windows API use
  WINDOWS_PORT_REFERENCE_REQUIRED   direct USER window/message/paint/geometry/focus/capture API use
  WINDOWS_PORT_REFERENCE_OPTIONAL   Windows-only helpers of lesser importance (GDI-only adapters, profile/INI, misc)
  OBSOLETE_WINDOWS_FEATURE          multimedia/MCI/DDE/Help/printing-only integration
  UNKNOWN_NEEDS_TRIAGE              no DOS pair and no Windows API use
The class is a proposal for supervisor review, recorded as such; the final classification lives in
docs/portable-windows-reference.md.
"""
import argparse
import json
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, cards, recipes, write_json

# USER APIs that define the host-window contract (window lifetime, messages, paint, geometry, focus, capture).
CORE_USER = {
    'CREATEWINDOW', 'CREATEWINDOWEX', 'DESTROYWINDOW', 'SHOWWINDOW', 'BRINGWINDOWTOTOP', 'SETWINDOWPOS', 'MOVEWINDOW',
    'GETWINDOWRECT', 'GETCLIENTRECT', 'CLIENTTOSCREEN', 'SCREENTOCLIENT', 'ADJUSTWINDOWRECT', 'INVALIDATERECT',
    'INVALIDATERGN', 'VALIDATERECT', 'VALIDATERGN', 'UPDATEWINDOW', 'BEGINPAINT', 'ENDPAINT', 'GETUPDATERGN',
    'GETUPDATERECT', 'PEEKMESSAGE', 'GETMESSAGE', 'TRANSLATEMESSAGE', 'DISPATCHMESSAGE', 'POSTMESSAGE',
    'SENDMESSAGE', 'POSTQUITMESSAGE', 'DEFWINDOWPROC', 'CALLWINDOWPROC', 'SETCAPTURE', 'RELEASECAPTURE',
    'GETCAPTURE', 'SETFOCUS', 'GETFOCUS', 'GETACTIVEWINDOW', 'SETACTIVEWINDOW', 'ISWINDOWVISIBLE', 'ISICONIC',
    'ISZOOMED', 'ENUMCHILDWINDOWS', 'GETPARENT', 'SETPARENT', 'GETWINDOW', 'GETTOPWINDOW', 'REGISTERCLASS',
    'SETWINDOWTEXT', 'GETWINDOWTEXT', 'SETCURSOR', 'LOADCURSOR', 'SHOWCURSOR', 'SETCURSORPOS', 'GETCURSORPOS',
    'SETTIMER', 'KILLTIMER', 'SCROLLWINDOW', 'GETSYSTEMMETRICS', 'GETDC', 'RELEASEDC', 'GETWINDOWDC', 'ISWINDOW',
    'SETWINDOWLONG', 'GETWINDOWLONG', 'SETWINDOWWORD', 'GETWINDOWWORD', 'SETMENU', 'GETMENU', 'DRAWMENUBAR',
    'CHECKMENUITEM', 'ENABLEMENUITEM', 'TRACKPOPUPMENU', 'LOADMENU', 'CREATEMENU', 'APPENDMENU', 'GETSUBMENU',
    'MESSAGEBOX', 'DIALOGBOX', 'CREATEDIALOG', 'ENDDIALOG', 'ISDIALOGMESSAGE', 'GETASYNCKEYSTATE', 'GETKEYSTATE',
    'WINDOWFROMPOINT', 'CHILDWINDOWFROMPOINT', 'ENABLEWINDOW', 'ISWINDOWENABLED', 'SENDDLGITEMMESSAGE',
    'GETDLGITEM', 'SETDLGITEMTEXT', 'GETDLGITEMTEXT', 'WINHELP', 'OPENICON', 'CLOSEWINDOW', 'FLASHWINDOW',
}
OBSOLETE_MODULES = {'MMSYSTEM', 'DDEML', 'SOUND'}
OBSOLETE_NAMES = {'WINHELP', 'MCISENDCOMMAND', 'MCISENDSTRING', 'DDEINITIALIZE', 'DDECONNECT', 'OPENSOUND', 'CLOSESOUND',
                  'SETVOICENOTE', 'STARTSOUND', 'STOPSOUND', 'SETVOICEQUEUESIZE', 'SETVOICESOUND', 'WAITSOUNDSTATE',
                  'ESCAPE', 'STARTDOC', 'ENDDOC', 'STARTPAGE', 'ENDPAGE'}
OPTIONAL_NAMES = {'GETPROFILESTRING', 'GETPROFILEINT', 'WRITEPROFILESTRING', 'GETPRIVATEPROFILESTRING',
                  'GETPRIVATEPROFILEINT', 'WRITEPRIVATEPROFILESTRING', 'GETOPENFILENAME', 'GETSAVEFILENAME',
                  'OPENFILE', 'LOADSTRING', 'GETVERSION', 'GETWINFLAGS', 'GLOBALALLOC', 'GLOBALLOCK', 'GLOBALUNLOCK',
                  'GLOBALFREE', 'LOCALALLOC', 'LOCALFREE', 'GETTICKCOUNT', 'GETCURRENTTIME'}


def import_names():
    """(module, ordinal) -> import name, from the SDK import library."""
    from library_match import import_symbols
    table = {}
    for name, target in import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB').items():
        table[(target.get('module'), target.get('ordinal'))] = name.lstrip('_').upper()
    return table


def dos_pairs():
    """Win16 symbol -> best DOS pair (any confidence) from the DOS project's correspondence (read-only)."""
    try:
        import xver
        pairs = xver.pairs()
        exact = xver.exact_dos_functions()
    except Exception:
        return {}
    order = {'CONFIRMED': 0, 'HIGH': 1, 'MEDIUM': 2, 'LOW': 3, 'NAMED': 4}
    out = {}
    # The DOS project transfers reviewed Win16 names onto its functions (layout/symbols.json 'code', with the
    # evidence in each entry's history). A DOS function carrying the same name is a pairing too.
    try:
        symbols = json.loads((xver.DOS_ROOT / 'layout/symbols.json').read_text(encoding='utf-8')).get('code', {})
    except (OSError, ValueError):
        symbols = {}
    for name, info in symbols.items():
        if name.startswith(('f_', 'o0', 'o1', 'o2', 'fd_')):
            continue
        address = '%s:%04X:%04X' % (info.get('unit'), info.get('seg', 0), info.get('off', 0))
        why = ' '.join(h.get('why', '') for h in info.get('history') or [])
        conf = 'CONFIRMED' if 'CONFIRMED' in why else 'NAMED'
        out['_' + name] = dict(dos=name, dos_address=address, confidence=conf, dos_exact=address in exact)
        if name.isupper():
            out[name] = out['_' + name]
    for p in pairs:
        w = p.get('win16')
        if not w:
            continue
        row = dict(dos=p.get('dos'), dos_address=p.get('dos_address'), confidence=p.get('confidence'),
                   dos_exact=p.get('dos_address') in exact)
        if w not in out or order.get(row['confidence'], 9) < order.get(out[w]['confidence'], 9):
            out[w] = row
    return out


def audit():
    names = import_names()
    admitted = recipes()
    pairs = dos_pairs()
    all_cards = [c for c in cards() if c.get('ownership') == 'GAME']
    by_symbol = {c['symbol']: c for c in all_cards}
    ledger = {}
    try:
        import drafts
        ledger = drafts.load()
    except Exception:
        pass
    rows = {}
    callers = defaultdict(set)
    for c in all_cards:
        for call in c.get('calls', []):
            for n in call.get('names') or []:
                callers[n].add(c['symbol'])
    for c in all_cards:
        imports = Counter()
        for f in c.get('known_fixups', []):
            t = f.get('target') or {}
            if t.get('kind') == 'import':
                imports['%s.%s' % (t.get('module'), names.get((t.get('module'), t.get('ordinal')), '#%s' % t.get('ordinal')))] += len(f.get('sites') or [1])
        api = {k.split('.', 1)[1] for k in imports}
        modules = {k.split('.', 1)[0] for k in imports}
        callees = sorted({n for call in c.get('calls', []) for n in (call.get('names') or []) if n in by_symbol})
        entry = ledger.get(c['symbol']) or ledger.get(c['symbol'].lstrip('_')) or {}
        best = entry.get('best') or {}
        ratio = None
        if best.get('opcode_total'):
            ratio = round(best['opcode_matches'] / best['opcode_total'], 3)
        pair = pairs.get(c['symbol'])
        core = sorted(api & CORE_USER)
        if api & OBSOLETE_NAMES or (modules & OBSOLETE_MODULES and not core):
            proposal = 'OBSOLETE_WINDOWS_FEATURE'
        elif core:
            proposal = 'WINDOWS_PORT_REFERENCE_REQUIRED'
        elif api:
            proposal = 'WINDOWS_PORT_REFERENCE_OPTIONAL'
        elif pair:
            proposal = 'SHARED_WITH_DOS_IGNORE'
        else:
            proposal = 'UNKNOWN_NEEDS_TRIAGE'
        rows[c['symbol']] = dict(symbol=c['symbol'], segment=c.get('segment_name'), size=c['extent'].get('size'),
                                 admitted=c['symbol'] in admitted, ratio=1.0 if c['symbol'] in admitted else ratio,
                                 imports=dict(imports), core_user_api=core, dos=pair,
                                 callers=sorted(callers.get(c['symbol'], ())), callees=callees, proposal=proposal)
    # Distance (in call edges) from each function down to the nearest direct Windows API user: a shared
    # function that sits right above the adapter layer is part of the boundary.
    api_users = {s for s, r in rows.items() if r['imports']}
    dist = {s: 0 for s in api_users}
    frontier = list(api_users)
    while frontier:
        nxt = []
        for s in frontier:
            for caller in rows[s]['callers']:
                if caller in rows and caller not in dist:
                    dist[caller] = dist[s] + 1
                    nxt.append(caller)
        frontier = nxt
    for s, r in rows.items():
        r['api_distance'] = dist.get(s)
    return rows


def markdown(rows):
    lines = ['| class | functions | bytes | admitted | open |', '|---|---:|---:|---:|---:|']
    by = defaultdict(list)
    for r in rows.values():
        by[r['proposal']].append(r)
    for k in ('SHARED_WITH_DOS_IGNORE', 'WINDOWS_PORT_REFERENCE_REQUIRED', 'WINDOWS_PORT_REFERENCE_OPTIONAL',
              'OBSOLETE_WINDOWS_FEATURE', 'UNKNOWN_NEEDS_TRIAGE'):
        v = by.get(k, [])
        lines.append('| %s | %d | %d | %d | %d |' % (k, len(v), sum(x['size'] or 0 for x in v), sum(x['admitted'] for x in v),
                                                   sum(not x['admitted'] for x in v)))
    lines += ['', '## WINDOWS_PORT_REFERENCE_REQUIRED (proposed)', '', '| symbol | admitted/ratio | size | core USER APIs | DOS pair |', '|---|---|---:|---|---|']
    for r in sorted(by['WINDOWS_PORT_REFERENCE_REQUIRED'], key=lambda r: r['symbol']):
        lines.append('| %s | %s | %s | %s | %s |' % (r['symbol'], 'exact' if r['admitted'] else r['ratio'], r['size'],
                                                  ', '.join(r['core_user_api']), (r['dos'] or {}).get('dos') or '-'))
    return '\n'.join(lines) + '\n'


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--json', default=str(ROOT / 'build/port/audit.json'))
    ap.add_argument('--md', default=str(ROOT / 'build/port/audit.md'))
    args = ap.parse_args()
    rows = audit()
    write_json(Path(args.json), rows)
    Path(args.md).parent.mkdir(parents=True, exist_ok=True)
    Path(args.md).write_text(markdown(rows), encoding='utf-8')
    print(markdown(rows).split('\n## ')[0])
    print('json: %s  md: %s' % (args.json, args.md))


if __name__ == '__main__':
    main()
