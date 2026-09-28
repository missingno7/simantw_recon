"""DIAGNOSTIC ONLY: compile single-choice residue frontiers under extra MSC 7.00 optimisation letters
the profile catalog never tested (/Oa, /Os, /Ot, /Oc, /Oo, /Oz, no /Ow), keeping everything else of
the function's assigned profile, and report which variants reach strict exact or move the earliest
divergence. Never changes the catalog; results in build/supervisor/flag_sweep.json."""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import promote
import search
from residue_clusters import classify

c = json.load(open(ROOT / 'build/supervisor/residue_clusters_report.json'))
kinds = ('WRONG_REGISTER', 'WRONG_STACK_SLOT', 'RELOAD_OR_SPILL', 'EXPRESSION_SHAPE', 'FAR_POINTER')
targets = [r for k in kinds for r in c.get(k, []) if r['ratio'] >= 0.9][:int(sys.argv[1]) if len(sys.argv) > 1 else 24]
ledger = json.load(open(ROOT / 'evidence/recovery/drafts/index.json', encoding='utf-8'))


def variant(flags, how):
    out = list(flags)
    i = next(n for n, f in enumerate(out) if f.startswith('/O'))
    letters = out[i][2:]
    if how.startswith('+'):
        letters += how[1:]
    elif how.startswith('-'):
        letters = letters.replace(how[1:], '')
    out[i] = '/O' + letters
    return out


# Never record diagnostic-flag compiles in the draft ledger (they use non-assigned flags).
search.drafts.store = lambda *a, **k: False
search.drafts.note = lambda *a, **k: None

VARIANTS = ['base', '+a', '+s', '+t', '+c', '+o', '+z', '-w']
orig = promote.function_flags
results = {}
for r in targets:
    sym = r['symbol']
    entry = ledger.get(sym) or ledger.get(sym.lstrip('_')) or {}
    src = (entry.get('frontier') or entry.get('best') or {}).get('source')
    if not src:
        continue
    row = {}
    for v in VARIANTS:
        def patched(symbol, _v=v):
            prof, flags = orig(symbol)
            return prof, (flags if _v == 'base' else variant(flags, _v))
        search.function_flags = patched
        promote.function_flags = patched
        try:
            rep = search.search(sym, [str(ROOT / src)], None, None, None, True, 'masm600', None, False, False)
            res = json.load(open(ROOT / rep['report'], encoding='utf-8'))['results'][0]['comparison']
            d = res.get('diagnostic') or {}
            kind, idx, _ = classify(d.get('aligned_asm') or [])
            row[v] = dict(result=res.get('result'), opcodes='%s/%s' % (d.get('opcode_matches'), d.get('opcode_total')), first=idx, kind=kind)
        except Exception as exc:
            row[v] = dict(error=str(exc)[:120])
        finally:
            search.function_flags = orig
            promote.function_flags = orig
    results[sym] = row
    base = row.get('base', {})
    better = [v for v in VARIANTS[1:] if row.get(v, {}).get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER')
              or (row.get(v, {}).get('first') or 0) > (base.get('first') or 0)]
    print('%-24s base %-9s first %-4s | %s' % (sym, base.get('opcodes'), base.get('first'),
          ' '.join('%s:%s@%s' % (v, row[v].get('opcodes'), row[v].get('first')) for v in better) or 'no variant better'), flush=True)
json.dump(results, open(ROOT / 'build/supervisor/flag_sweep.json', 'w'), indent=1)
