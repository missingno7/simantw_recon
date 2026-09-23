# Branch pointer follow-up: bounded temporary declaration axis

This isolated research batch tests whether the automatic `menuChoice` pointer in
`PauseGame` and `SetPause` accounts for the two-byte repeated code drift. The
prior branch-pointer listing uses `enter 2,0` in both routines, while the target
prologues use `push bp; mov bp,sp` and have no local frame. The target also
selects the near string offset in AX and pushes DS for the far call. This
supports a narrow register/type test for the temporary; no direct conditional
expression, new string layout, or production unit was changed.

The batch uses MSC 7.00 `/AL /G2 /Gs /Oelw /NTSIMANT_MODULE` and four forms:
`char near *`, `register char near *`, `char far *`, and `register char far *`.
All four compiled. They produced two distinct OMFs: the two near forms are
identical (SHA-256 `2e7a6b9185cd68e0cd9975e3ab2b613325c5616c027e4bf6c9531e17c4a63179`),
and the two far forms are identical (SHA-256
`e7f21265997a2e216eea84411983d6c48c00db532c579c03a829caf0526e1991`). C7
therefore ignored `register` for each tested type.

Neither form converged on the target layout. Every object has 930 code bytes;
the near forms retain `enter 2,0` and the far forms use `enter 4,0`. The near
forms keep `_PauseGame=158`, `_SetPause=530`, `_ProcMenuHelp=902`, versus target
0, 158, 528, 898. The far forms have the same public offsets. All four strict
comparisons report `RULED_OUT_MEMBER` for inconsistent public placements.
There is no exact body or complete contribution proof, so this batch provides
no recovery credit and no basis for admission.

The result converges the suggested pointer declaration axis: near `register`
does not remove the local frame, and changing the pointee to far preserves the
code size while enlarging the frame. The observed repeated excess remains
unresolved. Full receipts and diagnostics are in `run/results.json`, with the
four source variants under `run/` and compact identities in `evidence.json`.
