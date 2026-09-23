# AddRocks source recovery

The packet shows two counted passes: six fixed orientations using `_AddRock5`
and six using `_AddRock3`, each with fresh bounded `_SRand1` coordinates. The
first pass repeats `SRand1(3)+2` times; the second repeats twice that count.
`first.c` encodes the calls explicitly and preserves the observed argument
push order. One production test reproduced all 440 body bytes and all 37
semantic fixups, with no private contribution. The exact immutable candidate
under `evidence/recovery/workflow/jobs/AddRocks-01eddceee1/attempt01/` passed
fresh independent promotion to `src/recovered/wf_AddRocks-01eddceee1.c`.
