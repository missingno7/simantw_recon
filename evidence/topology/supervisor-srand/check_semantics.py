"""Exhaustive seed-transition audit, not an object recovery proof."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

def target(seed):
    carry = seed >> 15
    shifted = (seed << 1) & 0xffff
    return shifted ^ (0x1bf5 if carry else 0)

def widened(seed):
    value = seed * 2
    if value & 0x10000:
        value ^= 0x1bf5
    return value & 0xffff

def wrong_post_shift_sign(seed):
    value = (seed << 1) & 0xffff
    return value ^ (0x1bf5 if value & 0x8000 else 0)

def main():
    wrong = []
    for seed in range(65536):
        assert widened(seed) == target(seed), seed
        if wrong_post_shift_sign(seed) != target(seed):
            wrong.append(seed)
    report = dict(scope='Seed transition equivalence only; no compiler, ABI, frame, binding or recovery proof.',
                  seeds_checked=65536, widened_mismatches=0,
                  wrong_post_shift_sign_mismatches=len(wrong),
                  first_counterexample=dict(seed=wrong[0], target=target(wrong[0]), wrong=wrong_post_shift_sign(wrong[0])),
                  result_projection='Equal 16-bit next seeds imply equal masks for SRand2..256 and unsigned remainder for SRand1 for every nonzero divisor. Divisor zero is excluded.',
                  next_experiment='One bounded widened unsigned-long carry expression probe with a private unsigned seed and volatile result to express the observed stack store/reload; compare full object. No family-wide search unless it matches.')
    (Path(__file__).parent/'semantics.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))

if __name__ == '__main__':
    main()
