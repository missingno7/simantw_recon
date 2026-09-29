"""One owner per historical object (build-topology component) for canonical unit composition.

    python tools/unit_owner.py list
    python tools/unit_owner.py claim COMPONENT --owner NAME --reason TEXT [--hours 24]
    python tools/unit_owner.py release COMPONENT --owner NAME [--note TEXT]
    python tools/unit_owner.py check COMPONENT --owner NAME

Parallel workers may investigate individual functions of any object. Growing the
canonical unit of an object (tu_assembly compose --persist, promote.py --unit) is
done by that object's current owner only, so two workers never compose conflicting
declaration sets, stale unit ids or overlapping bytes. An unclaimed component is
free (the supervisor composes it). A claim expires after its lease, so a crashed
worker never blocks an object for long. layout/unit-owners.json keeps the current
claims and an append-only history for audit.
"""
import argparse
import json
import os
import sys
from datetime import datetime, timedelta, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError, read_json, write_json

PATH = ROOT / 'layout/unit-owners.json'
LOCK = ROOT / 'build/locks/unit-owners.lock'
SUPERVISOR = ('supervisor', 'sweep')


def _now():
    return datetime.now(timezone.utc)


def _iso(value):
    return value.strftime('%Y-%m-%dT%H:%M:%SZ')


def load(path=None):
    path = Path(path or PATH)
    return read_json(path) if path.exists() else dict(claims={}, history=[])


def _lock():
    from publication import file_lock
    return file_lock(LOCK, 60, 'unit ownership ledger is busy')


def active(claim, now=None):
    if not claim:
        return False
    try:
        until = datetime.fromisoformat(claim['until'].replace('Z', '+00:00'))
    except (KeyError, ValueError, AttributeError):
        return False
    return (now or _now()) < until


def owner_of(component, path=None):
    claim = load(path)['claims'].get(component)
    return claim if active(claim) else None


def claim(component, owner, reason, hours=24.0, path=None):
    if not owner or not reason:
        raise FormatError('claim needs --owner and --reason')
    with _lock():
        data = load(path)
        current = data['claims'].get(component)
        if active(current) and current['owner'] != owner:
            raise FormatError('component %s is owned by %s until %s (%s)' % (component, current['owner'], current['until'], current.get('reason')))
        now = _now()
        data['claims'][component] = dict(owner=owner, reason=reason, since=(current or {}).get('since') if active(current) else _iso(now),
                                         until=_iso(now + timedelta(hours=hours)))
        data['history'].append(dict(action='claim', component=component, owner=owner, reason=reason, time=_iso(now), hours=hours))
        write_json(Path(path or PATH), data)
        return data['claims'][component]


def release(component, owner, note='', path=None):
    with _lock():
        data = load(path)
        current = data['claims'].get(component)
        if current and active(current) and current['owner'] != owner and owner not in SUPERVISOR:
            raise FormatError('component %s is owned by %s, not %s' % (component, current['owner'], owner))
        data['claims'].pop(component, None)
        data['history'].append(dict(action='release', component=component, owner=owner, note=note, time=_iso(_now())))
        write_json(Path(path or PATH), data)


def require(component, owner=None, path=None):
    """Fail closed when another owner holds a live claim on COMPONENT (used before canonical composition)."""
    owner = owner or os.environ.get('SIMANTW_WORKER') or 'supervisor'
    current = owner_of(component, path)
    if current and current['owner'] != owner:
        raise FormatError('unit composition of %s belongs to %s until %s; coordinate with the supervisor (tools/unit_owner.py)'
                          % (component, current['owner'], current['until']))
    return owner


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='command', required=True)
    sub.add_parser('list')
    p = sub.add_parser('claim'); p.add_argument('component'); p.add_argument('--owner', required=True); p.add_argument('--reason', required=True); p.add_argument('--hours', type=float, default=24.0)
    p = sub.add_parser('release'); p.add_argument('component'); p.add_argument('--owner', required=True); p.add_argument('--note', default='')
    p = sub.add_parser('check'); p.add_argument('component'); p.add_argument('--owner')
    args = ap.parse_args()
    if args.command == 'list':
        data = load()
        print(json.dumps({c: dict(v, active=active(v)) for c, v in data['claims'].items()}, indent=2))
    elif args.command == 'claim':
        print(json.dumps(claim(args.component, args.owner, args.reason, args.hours), indent=2))
    elif args.command == 'release':
        release(args.component, args.owner, args.note)
        print('released')
    else:
        print(json.dumps(dict(component=args.component, owner=owner_of(args.component), may_compose_as=require(args.component, args.owner)), indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
