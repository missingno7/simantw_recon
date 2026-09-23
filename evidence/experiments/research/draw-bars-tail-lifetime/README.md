# DrawBar saved-edge lifetime probe

Isolated research only; the exhausted `_win_DrawHBar` and `_win_DrawVBar`
production jobs and complete-member proof inputs were not changed.

## Hypothesis

The target loads its saved edge into SI immediately after `win_UnlockWin`
(`mov si,[bp-4]` for HBar, `mov si,[bp-6]` for VBar), before pushing the
fixed-point divisor and fraction at `+0x63`. The preserved sources initialize
that edge in function scope, but C7 `/Oelw /GA` sinks its load until the first
arithmetic use at `+0x6a`. The new probe narrows the local's scope to a block
starting after `win_UnlockWin` and initializes it in the block declaration.

## Results

| Member | Strict result | Target bytes | Candidate bytes | Fixups | Effective object SHA-256 | Deduplicated against |
|---|---|---:|---:|---:|---|---|
| `_win_DrawHBar` | `NO_COMPLETE_MATCH` | 146/156 | 146/156 | 11/11 | `fd77593bfe35d11b91141a0033d556c27cb6b94a33548c1c0440132700c95f8c` | HBar attempt05 and attempt07 |
| `_win_DrawVBar` | `NO_COMPLETE_MATCH` | 145/158 | 145/158 | 11/11 | `52ff7b5e18061da454de68da46cbba04e9144b725795e6bbf3549c1785581c42` | VBar attempt08 |

HBar remains 192 bytes with 80/81 opcodes; the only instruction-order gap is
still the target's pre-push `mov si,[bp-4]` versus the candidate's post-push
load at `+0x6a`. VBar remains 194 bytes with 81/82 opcodes; the target loads
`[bp-6]` into SI before the pushes while the candidate loads it later and
retains the previously observed operand/register/local-layout differences.
The block lifetime and initialized-declaration spelling produce no new
effective object in either mirror. No candidate qualifies for production
reissue.

The next useful discriminator is source-level proof of how the original TU
made the saved edge register-live across the fixed-point helper call and the
foreground `GRectFill` call (e.g. an exact neighboring original source/member
with the same helper sequence). Repeating local declaration order, register
qualification, or algebraic spelling without such evidence is unlikely to
separate the current object classes.

## Reproduction

- `make_specs.py` derives each controlled source from the fresh
  `build/reclassify/*/candidate0000.c` source and emits the exact spec.
- `win_DrawHBar-result.json` and `win_DrawVBar-result.json` are compact
  codegen-grinder evidence records with the strict comparison and object
  identity.
- Candidate diffs are in `build/experiments/draw-bars-tail-lifetime-{h,v}/`.
