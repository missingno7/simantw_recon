import unittest
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import worker_validate
from common import FormatError
from common import identity


class WorkerValidationScalingTests(unittest.TestCase):
    def test_supported_counts_match_the_proof_gates(self):
        self.assertEqual(worker_validate.SUPPORTED_WORKERS, (1, 4, 8, 12, 16))

    def test_validation_refuses_an_unconfigured_count_before_compiling(self):
        with self.assertRaises(FormatError):
            worker_validate.validate_workers(3)

    def test_stress_refuses_an_unconfigured_count_before_starting_service(self):
        with self.assertRaises(FormatError):
            worker_validate.service_stress(3, 400)

    def test_latency_percentiles_are_stable_for_small_samples(self):
        self.assertEqual(worker_validate.percentile([], .5), None)
        self.assertEqual(worker_validate.percentile([4, 1, 3, 2], .5), 3)
        self.assertEqual(worker_validate.percentile([4, 1, 3, 2], .95), 4)

    def test_resource_summary_groups_compiles_per_host(self):
        def row(host, session, cpu, mem, read_bytes, write_bytes):
            return dict(receipt=dict(worker_id=host, worker_session=session,
                                     timing=dict(environment_launches=1),
                                     resource_delta=dict(cpu_seconds=cpu,
                                                         peak_working_set_bytes=mem,
                                                         read_transfer_bytes=read_bytes,
                                                         write_transfer_bytes=write_bytes,
                                                         read_operations=2,
                                                         write_operations=1)))
        summary = worker_validate.resource_summary(
            [row(0, 'W0_a', .5, 1024, 100, 50), row(0, 'W0_b', .25, 2048, 30, 20), row(1, 'W1_a', .4, 4096, 70, 40)],
            workers=2, elapsed=2)
        self.assertEqual(summary[0]['jobs'], 2)
        self.assertEqual(summary[0]['sessions'], 2)
        self.assertEqual(summary[0]['environment_launches'], 2)
        self.assertEqual(summary[0]['cpu_seconds'], .75)
        self.assertEqual(summary[0]['cpu_percent_of_one_core'], 37.5)
        self.assertEqual(summary[0]['peak_working_set_bytes'], 2048)
        self.assertEqual(summary[0]['read_transfer_bytes'], 130)
        self.assertEqual(summary[1]['jobs'], 1)

    def test_canonical_omf_comparison_uses_full_recorded_identity(self):
        import tempfile
        with tempfile.TemporaryDirectory() as directory:
            obj = Path(directory) / 'OUTPUT.OBJ'
            obj.write_bytes(b'canonical OMF bytes')
            row = dict(receipt=dict(object_identity=identity(obj)))
            self.assertTrue(worker_validate.canonical_object_equal(obj, row))
            obj.write_bytes(b'different OMF bytes')
            self.assertFalse(worker_validate.canonical_object_equal(obj, row))


if __name__ == '__main__':
    unittest.main()
