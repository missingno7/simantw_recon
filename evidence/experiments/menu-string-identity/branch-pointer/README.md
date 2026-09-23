# Explicit branch pointer assignment probe

This isolated MSC 7.00 `/AL /G2 /Gs /Oelw /NTSIMANT_MODULE` probe tests a
single 32-byte near array and explicit `if`/`else` assignments to a local near
pointer before one `SetMenuOptionText` call in each of `_SetMenuEntries`,
`_PauseGame`, and `_SetPause`. It uses the existing `simant:4C24` unit source
and baseline profile. The production unit, job, and manifests were not edited.

Source: `candidate.c` (4549 bytes, SHA-256
`b0cf4050bd21b53d9f5cdb6530897a8e348f2d8a2880f033fcb876dc22b62588`). The
compiler input snapshot is `run/candidate0000.c` (4698 bytes, SHA-256
`8a708663b34f7c45aed225834d802012e3ca22cc7d1c92f8e0082d3b2c33e03a`). The
effective OMF is 2022 bytes, SHA-256
`2e7a6b9185cd68e0cd9975e3ab2b613325c5616c027e4bf6c9531e17c4a63179`. This is
one unique OMF among this one-candidate batch and differs from the two prior
effective objects (`9037a8f2…` and `e501a023…`) recorded in the parent
`alignment-probes.json`.

The OMF has 930 bytes of `SIMANT_MODULE` code and 32 bytes of `_DATA`. Public
offsets are `_SetMenuEntries=0`, `_PauseGame=158`, `_SetPause=530`, and
`_ProcMenuHelp=902`; the target offsets are 0, 158, 528, and 898. Thus shared
DATA length is right, while the later public placements diverge.

Strict comparison result: `RULED_OUT_MEMBER`, issue `inconsistent public
placements for SIMANT_MODULE`. The strict member matcher therefore did not
validate a complete set of code/data/fixup contributions. This is not proof or
recovery credit. Full compiler receipt, object parse, strict report, and
diagnostic diff are retained in `run/results.json` and
`run/candidate0000.diff.txt`.
