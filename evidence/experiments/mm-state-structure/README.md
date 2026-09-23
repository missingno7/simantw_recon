# Multimedia state and `_vocMciClose` unit

The original `_vocMciClose` body was exact, but its three separate based
statics collapsed onto adjacent words in an isolated object. The target
addresses are `SIMANT_DATA_GROUP:8D08` (module handle), `8D14` (wave handle),
and `8D1A` (reference count). Target users also touch the intervening state
words. A 20-byte structured, zero-initialized based object at 8D08 gives
authentic MSC 7.00 complete isolated comparisons with no issues for both
`_IsMMMidiAvail` and `_vocMciClose` (`*-struct-trial/`). This tests layout;
the names/types of fields unused by these claimed members remain provisional.

The previous availability sources reached their procedure-name strings by
adding 6 and 0x18 to the MAPSYM word `_wSoundBlasterMsg` at DGROUP 0AF4.
Target DGROUP contains three adjacent named words at 0AF4/0AF6/0AF8, then
`"midiOutGetNumDevs"` at 0AFA and `"waveOutGetNumDevs"` at 0B0C. Authentic
literal-source probes (`IsMMMidiAvail-literal-trial/` and
`IsMMWaveAvail-literal-trial/`) match those strings, code, selector, and far
state without the cross-object array alias. `_vocMciClose` uses the third
`"waveOutClose"` copy at 0C6D; the isolated literal trial retains its code
shape but cannot place it next to its 0AF0/0AF2 flags without intervening
data.

`reviewed-unit.c` composes `_vocMciClose` with ten already admitted members.
It defines the two private near flags, the three MAPSYM near words at
0AF4/0AF6/0AF8, and the shared far state. Two explicitly noncredited
`POOLSTUB_TEXT` functions emit the exact intervening string literals for
unrecovered sound members. They are construction aids, not recovered
functions. The original DGROUP 0AF0-0CAA span has no NE relocations. The
reviewed unit matched all claimed code (including 122 bytes for
`_vocMciClose`), 454 DATA bytes, two CONST bytes, 20 far-state bytes, and
the ordinary/fixup obligations in a fresh independent admission:
`evidence/recovery/workflow/jobs/tu_gr_7712_IsMMMidiAvail_11_reviewed-20da90de50/promotion.json`.
The older individual job `vocMciClose-671a37cab0` is linked as superseded;
its failed isolated trial remains in history.

`_snd_IsSongDone` is a bounded follow-up, not an admission. Its 44-byte target
loads ES once from selector slot BF78, tests state words at 8D08/8D0C/8D0A,
then compares 8D1C with one and returns the unsigned-borrow Boolean through
`SBB AX,AX; NEG AX`. Extending the admitted state declaration from 20 to 22
bytes and adding this source to a twelve-member reviewed unit failed private
placement for `SIMANT_DATA_GROUP`; isolated C7 emits an immediate segment
load and a conditional branch at the Boolean tail. Reversing the unsigned
comparison spelling compiled identically. `snd_IsSongDone*-trial/` and
`gr_7712_IsMMMidiAvail_12_reviewed/` preserve the negative evidence. The
8D1C word is adjacent to the admitted state, but this does not establish that
it is a field of that same C object.
