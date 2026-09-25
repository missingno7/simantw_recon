"""Complete validation at acceptance or tooling boundaries (not for every hypothesis).

Runs the unit/negative tests, independently re-verifies every admitted object
against the original executable, checks catalogued compiler profiles, replays
an exact control through the compiler cache and checks the persistent-service
evidence. Writes build/validation/report.json and refreshes docs/progress.json.
"""
import json
import re
import subprocess
import sys
from common import ROOT, FormatError, identity, read_json, recipes, write_json
from publication import publication_lock, recover, timestamp

CONTROL = '_TooFar'


def main():
    output = ROOT / 'build/validation'
    output.mkdir(parents=True, exist_ok=True)
    report = dict(checked=timestamp(), passed=False)
    command = [sys.executable, '-m', 'unittest', 'discover', '-s', 'tests']
    tests = subprocess.run(command, cwd=ROOT, capture_output=True, timeout=1200)
    log = (tests.stdout + tests.stderr).decode('utf-8', errors='replace')
    (output / 'tests.log').write_text(log, encoding='utf-8')
    count = re.search(r'Ran (\d+) tests', log)
    report['tests'] = dict(exit_code=tests.returncode, count=int(count.group(1)) if count else None, log='build/validation/tests.log')
    if tests.returncode:
        write_json(output / 'report.json', report)
        raise FormatError('tests failed; see build/validation/tests.log')

    import compiler_profiles
    compiler_profiles.validate()
    with publication_lock():
        report['publication_journal'] = recover()['status']
        from verify_recovery import verify
        verified = verify(publish=True)
    report['recovery'] = {k: v for k, v in verified.items() if k not in ('game', 'runtime')}
    from image import build as build_image
    whole = build_image()
    if whole['status'] != 'HYBRID_EXACT':
        raise FormatError('whole-image rebuild is not exact: ' + '; '.join(whole['problems'][:5]))
    report['image'] = {k: whole[k] for k in ('status', 'owned', 'debt', 'debt_total', 'claim_conflicts')}

    # An admitted control compiled twice through the cache: replay must reuse
    # the object without a compiler launch and still rematch strictly.
    from codegen_grinder import GOOD, run
    target = recipes()[CONTROL]
    spec = dict(symbol=CONTROL, source=target['source'], compiler=target['compiler'], flags=target['flags'], publics=[CONTROL], max_candidates=1)
    first = run(spec, 'build/validation/cache-first', cache=True)
    replay = run(spec, 'build/validation/cache-replay', cache=True)
    if replay['cache']['hits'] != replay['candidates'] or replay['environment_launches']:
        raise FormatError('cache replay recompiled the control')
    if replay['results'][0]['comparison']['result'] not in GOOD:
        raise FormatError('admitted control no longer matches strictly')
    if [r['comparison']['result'] for r in first['results']] != [r['comparison']['result'] for r in replay['results']]:
        raise FormatError('fresh comparisons differ after cache replay')
    report['cache_replay'] = dict(control=CONTROL, result=replay['results'][0]['comparison']['result'], cache=replay['cache'])

    runner = read_json(ROOT / 'evidence/experiments/runner/service-stress.json')
    if not runner['passed'] or runner['jobs'] < 400 or any(identity(ROOT / p) != expected for p, expected in runner['inputs'].items()):
        raise FormatError('persistent compiler-service stress evidence is missing or stale; rerun tools/worker_validate.py')
    report['compiler_service'] = dict(evidence='evidence/experiments/runner/service-stress.json', jobs=runner['jobs'])
    report['passed'] = True
    write_json(output / 'report.json', report)
    print(json.dumps(dict(passed=True, tests=report['tests']['count'], recovery=report['recovery'], image=report['image'], cache_replay=report['cache_replay']['result']), indent=2))


if __name__ == '__main__':
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))
