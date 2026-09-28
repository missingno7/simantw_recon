import json
import os
import sys
import tempfile
import time
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import compiler_service as service
from common import FormatError, identity, write_json


class WorkerProofTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        for relative in service.PROOF_INPUTS:
            path = self.root / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(relative)
        write_json(self.root / 'evidence/experiments/toolchain/msc700-baseline-Oelw.json', dict(results=[]))
        self.inputs = {relative: identity(self.root / relative) for relative in service.PROOF_INPUTS}
        self.proof_dir = self.root / 'evidence/experiments/runner'
        self.proof_dir.mkdir(parents=True)

    def tearDown(self):
        self.temp.cleanup()

    def write_proof(self, workers, passed=True, recorded_workers=None):
        write_json(self.proof_dir / ('worker-%d.json' % workers),
                   dict(workers=workers if recorded_workers is None else recorded_workers,
                        passed=passed, inputs=self.inputs))

    def test_exact_proven_count_is_accepted(self):
        self.write_proof(8)
        with patch.object(service, 'ROOT', self.root):
            proof = service.require_worker_proof(8)
        self.assertEqual(proof['workers'], 8)

    def test_unproven_count_is_refused(self):
        with patch.object(service, 'ROOT', self.root):
            with self.assertRaises(FormatError):
                service.require_worker_proof(12)

    def test_proof_for_different_count_is_refused(self):
        self.write_proof(8, recorded_workers=4)
        with patch.object(service, 'ROOT', self.root):
            with self.assertRaises(FormatError):
                service.require_worker_proof(8)

    def test_stale_input_identity_is_refused(self):
        self.write_proof(8)
        (self.root / service.PROOF_INPUTS[0]).write_text('changed')
        with patch.object(service, 'ROOT', self.root):
            with self.assertRaises(FormatError):
                service.require_worker_proof(8)

    def test_probe_source_and_expected_omf_are_bound_to_the_proof(self):
        source = self.root / 'evidence/experiments/toolchain/probes/probe.c'
        expected = self.root / 'build/compiler-jobs/oracle/OUTPUT.OBJ'
        source.parent.mkdir(parents=True, exist_ok=True)
        expected.parent.mkdir(parents=True, exist_ok=True)
        source.write_text('int probe(void) { return 1; }')
        expected.write_bytes(b'canonical object')
        source_identity = identity(source)
        object_identity = identity(expected)
        write_json(self.root / 'evidence/experiments/toolchain/msc700-baseline-Oelw.json',
                   dict(results=[dict(receipt=dict(source='evidence/experiments/toolchain/probes/probe.c',
                                                  source_identity=source_identity,
                                                  object='build/compiler-jobs/oracle/OUTPUT.OBJ',
                                                  object_identity=object_identity))]))
        with patch.object(service, 'ROOT', self.root):
            inputs = service.current_proof_inputs()
            write_json(self.proof_dir / 'worker-8.json', dict(workers=8, passed=True, inputs=inputs))
            service.require_worker_proof(8)
            expected.write_bytes(b'changed object')
            with self.assertRaises(FormatError):
                service.require_worker_proof(8)

    def test_recorded_omf_identity_is_pinned_when_oracle_bytes_are_absent(self):
        source = self.root / 'evidence/experiments/toolchain/probes/probe.c'
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text('int probe(void) { return 1; }')
        expected = dict(size=15, sha256='a' * 64)
        write_json(self.root / 'evidence/experiments/toolchain/msc700-baseline-Oelw.json',
                   dict(results=[dict(receipt=dict(source='evidence/experiments/toolchain/probes/probe.c',
                                                  source_identity=identity(source),
                                                  object='build/compiler-jobs/oracle/OUTPUT.OBJ',
                                                  object_identity=expected))]))
        with patch.object(service, 'ROOT', self.root):
            inputs = service.current_proof_inputs()
        self.assertEqual(inputs['oracle-omf:build/compiler-jobs/oracle/OUTPUT.OBJ'], expected)

    def test_oracle_paths_cannot_escape_the_worktree(self):
        write_json(self.root / 'evidence/experiments/toolchain/msc700-baseline-Oelw.json',
                   dict(results=[dict(receipt=dict(source='../outside.c', object='build/oracle.obj'))]))
        with patch.object(service, 'ROOT', self.root):
            with self.assertRaises(FormatError):
                service.current_proof_inputs()

    def test_unlisted_count_is_refused(self):
        with patch.object(service, 'ROOT', self.root):
            with self.assertRaises(FormatError):
                service.require_worker_proof(3)


class TransientRetentionTests(unittest.TestCase):
    def test_prunes_only_old_terminal_transport_records(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            base = root / 'service'
            for name in ('completed', 'jobs', 'pending', 'running', 'requests'):
                (base / name).mkdir(parents=True)
            old = time.time() - 90000
            fresh = time.time()

            stale_result = base / 'completed/stale.json'
            stale_result.write_text(json.dumps(dict(object='build/compiler-jobs/keep.obj')))
            os.utime(stale_result, (old, old))
            fresh_result = base / 'completed/fresh.json'
            fresh_result.write_text('{}')
            os.utime(fresh_result, (fresh, fresh))

            terminal = base / 'jobs/terminal'
            terminal.mkdir()
            (terminal / 'INPUT.C').write_text('source snapshot')
            marker = terminal / 'request-completed.json'
            marker.write_text('{}')
            os.utime(marker, (old, old))
            os.utime(terminal, (old, old))

            incomplete = base / 'jobs/incomplete'
            incomplete.mkdir()
            (incomplete / 'INPUT.C').write_text('keep queued snapshot')
            os.utime(incomplete, (old, old))
            pending = base / 'pending/queued.json'
            pending.write_text('{}')
            running = base / 'running/active.json'
            running.write_text('{}')
            request = base / 'requests/batch.json'
            request.write_text('{}')
            object_file = root / 'build/compiler-jobs/keep.obj'
            object_file.parent.mkdir(parents=True)
            object_file.write_bytes(b'cached compile result')

            with patch.object(service, 'BASE', base):
                removed = service.prune_transient(now=time.time(), max_age_seconds=86400)

            self.assertEqual(removed, dict(completed=1, jobs=1))
            self.assertFalse(stale_result.exists())
            self.assertTrue(fresh_result.exists())
            self.assertFalse(terminal.exists())
            self.assertTrue(incomplete.exists())
            self.assertTrue(pending.exists())
            self.assertTrue(running.exists())
            self.assertTrue(request.exists())
            self.assertEqual(object_file.read_bytes(), b'cached compile result')


if __name__ == '__main__':
    unittest.main()
