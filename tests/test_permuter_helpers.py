"""Helper-mode controls use the same fixup-bound path as static_probe."""
import sys
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import permuter
from common import FormatError


def test_helper_batch_timeout_is_split_until_candidates_are_isolated():
    worker = object.__new__(permuter.Permuter)
    worker.counts = {'compiler_batch_retries': 0}
    calls = []

    def compile_cached(jobs, compiler):
        calls.append(len(jobs))
        if len(jobs) > 1:
            raise FormatError('persistent compiler job timeout')
        return [(Path('candidate.obj'), {'exit_code': 0})], {
            'hits': 0, 'misses': 1, 'environment_launches': 1}

    with mock.patch('codegen_cache.compile_cached', side_effect=compile_cached):
        compiled, cache = worker._compile_helper_jobs([{'source': str(i)} for i in range(3)])
    assert len(compiled) == 3
    assert all(obj is not None for obj, _receipt in compiled)
    assert cache == {'hits': 0, 'misses': 3, 'environment_launches': 3}
    assert worker.counts['compiler_batch_retries'] == 2
    assert calls == [3, 1, 2, 1, 1]


def test_admitted_antedit_static_helper_scores_exact():
    # ScrollEditBy is an admitted private helper at 3:616C in this recovered
    # antedit unit. The source TU is its real caller context and profile anchor.
    source = ROOT / 'src/recovered/tu_antedit_00F4_OverlayTileSet_22_reviewed-c56efa1dba.c'
    args = SimpleNamespace(
        seed=7001,
        out=str(ROOT / 'build/permuter/test_helper_admitted_616c'),
        batch_size=2,
        beam=1,
        allow_risky=False,
        only=None,
    )
    worker = permuter.Permuter(source, 'ScrollEditBy', args,
                               helper='3:616C', like='_CenterEdit')
    try:
        worker.evaluate_baselines()
        assert worker.baseline_original.score['strict_exact'] is True
        assert worker.baseline_original.score['frame_equal'] is True
        assert worker.baseline_original.score['aligned_cost'] == 0
        assert worker.baseline_original.score['first_divergence_row'] > 96
        assert worker.baseline_original.comparison['diagnostic']['ordinary_bytes_equal'] is True
    finally:
        worker.close()
