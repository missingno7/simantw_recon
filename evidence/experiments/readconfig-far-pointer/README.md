# `_ReadConfig` far-object ABI probe

This research isolates the two selector-backed objects used by `_ReadConfig`.
It does not change the production job or prove the rest of the parser.

## Positive result

Under the assigned MSC C 7.00 profile (`/AL /G2 /Gs /Oelw /NTGR_MODULE`),
declare each object as a **far object whose stored value is a far `char *`**:

```c
extern char far * far configFileName;
extern char far * far configFileMissingStr;
```

Pass the filename pointer value directly to the Pascal `_lopen` import:

```c
_lopen(configFileName, 0);
```

The paired fixture in [`pair_probe.py`](pair_probe.py) emits this sequence for
the filename:

```asm
mov es, word ptr [selector_slot_0]
push word ptr es:[object_offset + 2]
push word ptr es:[object_offset]
push 0
lcall _lopen
```

For the error string, a later reference emits a second selector load from
`selector_slot_1`. These are the same two consecutive selector-pool words
observed at DGROUP `0xC6AE` and `0xC6B0`. The MAPSYM objects are at
`GR_MODULE:0x8B36` (`_configFileName`) and `GR_MODULE:0x8B32`
(`_configFileMissingStr`); the generated object fixups name those exact
externals, with the high word read before the low word as in the target.

## Scoped negatives

The single-object sweep in [`probe.py`](probe.py) compiles eight declaration /
expression forms and deduplicates by code bytes plus semantic fixups. Five
effective output classes remained:

- `char far * far` passed directly, and the equivalent far-pointer-array form,
  produce the target's selector load followed by direct reads from the object.
- An additional pointer level (`char far * far * far`) adds `LES` and an
  indirect dereference through `BX`; it is not the target idiom. `*p` and
  `p[0]` collapse to the same output in this probe.
- A near pointer object emits direct DS memory reads without the selector
  load.
- A far character array passes its address instead of loading a stored far
  pointer.

The paired probe also tested one-level versus triple-level declarations for
both globals. Each distinct pair changed the generated code; keeping the
filename at one far-pointer level and adding a pointer level to the error
string changes only the second load, and vice versa. Therefore the evidence
supports a one-level stored far pointer for **both** globals.

## Evidence and limits

[`results.json`](results.json) and [`pair-results.json`](pair-results.json)
retain the C7 object hashes, disassembly, fixups, profile and effective-output
classes. The fixtures are structural ABI probes: external symbol offsets are
unresolved placeholders, so the expected `0x8B36` / `0x8B32` displacements
follow from linking the same named externals at the MAPSYM locations. This
does not prove the parser body, MessageBox argument source ordering, private
data, or the complete member. Production remains escalated.

## Preserved-candidate re-test

[`candidate.c`](candidate.c) is an isolated copy of the best production draft
with only the filename declaration corrected to one far-pointer level and the
call changed from `*configFileName` to `configFileName`. It was compiled and
strictly compared under the assigned profile using
[`retest-spec.json`](retest-spec.json); the escalated production job was not
reopened or edited.

The first call now matches the target's two pointer-word pushes and Pascal
`_lopen` call at the same code offsets. The selector-load instruction still
compares as a candidate `CONST` fixup against the target's linked absolute
DGROUP operand. The full result remains `NO_COMPLETE_MATCH`: 4/36 fixups match
and 36/511 compared literal bytes match, with a 506-byte candidate body
against the 548-byte target extent. Immediately after `_lopen` returns a
nonpositive handle, the target loads the second selector and its far object
into registers at offsets 34–49. This candidate lacks that open-failure
`MessageBox` / `exit` path and instead uses the missing-file string in its
later invalid-token case. That source control-flow/meaning error remains,
alongside private `CONST` placement. The
candidate object hash is distinct from all four production attempt objects.
See [`retest-summary.json`](retest-summary.json) for the dedup check and
opening alignment; the full matcher output is under [`retest/`](retest/).

## Shared failure message branch

The target's nonpositive `_lopen` branch and its invalid-display default share
one `MessageBox` / `exit` block. The bounded layouts in
[`branch_probe.py`](branch_probe.py) first confirmed that placing a direct
`MessageBox` in the open-failure `if` creates a separate early call and does
not reproduce the target's jump-to-common-call sequence.

[`common_error_probe.py`](common_error_probe.py) gives both paths a local far
message pointer and one common label. That reproduces the target's first
failure setup through `mov cx, ax` and the store of the selector to `[bp-6]`.
[`inline_error_probe.py`](inline_error_probe.py) places the common label in the
switch default, matching the target's block ordering more closely. Its output
matches the complete open-failure argument setup, local pointer slot, caption
pushes, type value, and `MessageBox` call shape. The remaining differences
include the selector load as an unresolved `CONST` fixup, a candidate fixup
for `rootWnd` where the target uses the linked absolute DGROUP operand, and
the jump landing at the candidate's differently placed shared block.

That best branch candidate remains `NO_COMPLETE_MATCH`: 9/37 fixups,
54/504 literal bytes, and 199/219 opcodes align diagnostically. Its OMF hash
is distinct from the four production attempts, the far-object retest, the
direct-branch controls, and the first common-label placement. Compact
alignment and result data are in
[`inline-error-summary.json`](inline-error-summary.json); complete strict
evidence is under [`branch-run/inline-error/`](branch-run/inline-error/).
Production remains escalated.
