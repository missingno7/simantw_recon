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

`_snd_IsSongDone` is now admitted in a twelve-member replacement unit. Its
44-byte target loads ES once from selector BF78, tests state words at
8D08/8D0C/8D0A, then compares 8D1C with one and returns the unsigned-borrow
Boolean through `SBB AX,AX; NEG AX`. The admitted `_ProcEditEvent` supplied a
control: `songState == 0` makes authentic C7 emit that Boolean tail. An
`extern __segment near` word used in a based view of the state produced the
correct four-byte selector load, while `__based(__segname(...))` or an ordinary
`extern far` object produced a five-byte immediate segment load. The isolated
`snd_IsSongDone-selector-alias-trial/` matches all 44 code bytes, five code
bindings, the two-byte selector relocation and 22 far-state bytes.

The first 22-byte unit failed because that five-byte load tried to bind a
segment fixup at target BF78 as a far-state offset, conflicting with the field
offset constraints. It did not disprove the 8D1C field identity. Its original
unit source, test, and diagnostics are retained under `failed-22byte-unit/`;
the separate-word and const-selector trials record additional rejected
representations. A `static const __segment near` selector, initialized from
`__segname("SIMANT_DATA_GROUP")`, and a based view of the same named object
reproduce the target's two-byte CONST selector slot without adding a near DATA
word. Using that view throughout the unit gives exact bodies for the eleven
earlier members and `_snd_IsSongDone`, the 454-byte DATA span, two CONST bytes,
and 22 far-state bytes. Fresh independent admission:
`evidence/recovery/workflow/jobs/tu_gr_7712_IsMMMidiAvail_12_reviewed-5d2b970b1c/promotion.json`.
The old individual `snd_IsSongDone-18a6b4f887` job is linked as superseded.
This establishes a coherent source representation and byte identity for the
claimed unit; it does not prove the original identifier or macro spelling.

The next control was `_MultiMediaSong`: its 51-byte target checks the near
`songsOnFlag` before loading BF78 and then tests state offsets 8D08, 8D0A,
8D0C, and 8D0E, sharing one false-return block. The isolated
`MultiMediaSong-selector-trial/` reproduced every instruction position but
left external selector/state bindings unresolved. Adding that body after the
twelve-member source in `reviewed-unit-multimedia-song.c` gave a complete
thirteen-member match: 982/982 ordinary bytes, all 44 fixups in claimed
contributions, 454 DATA bytes, two CONST bytes, and the same 22 far-state
bytes. The 28 other reported fixups are in explicitly noncredited stand-in
code. Fresh independent admission:
`evidence/recovery/workflow/jobs/tu_gr_7712_IsMMMidiAvail_13_reviewed-a2f2d7598c/promotion.json`.
The five-attempt individual job `MultiMediaSong-f2993ef613` is linked as
superseded. This second member confirms that the selector view is useful
beyond the single song-done spelling.

`_CheckMMWave` is admitted in the fourteen-member replacement unit. The old
individual job treated its inline `strlen` as requiring a different compiler
profile. Authentic C7 with baseline `/AL /G2 /Gs /Oelw /NTGR_MODULE` and
source-local `#pragma intrinsic(strlen)` emitted the target `REPNE SCASB`
sequence. The Win16 SDK `LIBW.LIB` import records identify KERNEL ordinal
134 as `GetWindowsDirectory`; the earlier `GetSystemDirectory` declaration
bound ordinal 135 and was wrong. Assigning `proc ? proc() : 0` to an `int
devices` local produces the target SI result join. The isolated
`CheckMMWave-result-local-trial/` preserves the exact positional body but
leaves private string and state bindings unresolved.

The first reviewed unit duplicated four strings and shifted near DATA;
`failed-duplicate-strings-unit/` preserves its comparison. The next named
all-five-string version added one alignment byte before `"MMSYSTEM.DLL"`;
`failed-aligned-library-name-unit/` preserves that result. The admitted
`reviewed-unit-check-mm-wave-mixed.c` shares four named near arrays with the
availability members: procedure names at DGROUP 0AFA/0B0C and system paths
at 0B1E/0B32. `LoadLibrary("MMSYSTEM.DLL")` stays a literal at odd 0B47.
The unit test at
`evidence/recovery/units/gr_7712_IsMMMidiAvail_14_reviewed/test/results.json`
reports all 1114 claimed ordinary code bytes and 57 claimed fixups exact,
plus 454 near DATA bytes, two CONST bytes, and 22 far-state bytes. The other
25 fixups are in explicitly noncredited stand-ins. Fresh independent
promotion is recorded at
`evidence/recovery/workflow/jobs/tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59/promotion.json`;
the previous thirteen members were reverified, and the zero-attempt
`CheckMMWave-9d5b57c59b` job was linked as superseded. This unit establishes
the source representation and complete member bytes, not the original
historical spelling of each near array.

`_mySongIsDone` remains open. Its target reads 8D06 before the admitted
8D08-based state, then checks the known near `songsOnFlag` and four admitted
state fields. Three bounded isolated C7 probes in
`mySongIsDone-*-shape-trial/` use a named selector and keep the 8D06 word as
a separate external. They match the 66-byte extent, selector-load position,
outer checks, and BX Boolean register, but C7 canonicalizes all three
source layouts to place the `songState == 0` block before the `result = 1`
block. The target places `result = 1` first and branches forward to the
comparison, then jumps back to the shared BX return. None is a complete
body or proves that 8D06 belongs to the 22-byte object. A new experiment
needs a causal explanation for this block order and a separate placement
test for the preceding word; more equivalent `if`/`goto` spellings are not
useful.

A further `mySongIsDone-branch-return-trial/` tested a branch-local return
before the final song-state test. It compiled to 58 bytes, moved the Boolean
into AX, and still placed the final test before the one-result block. This
rules out that simple return spelling; the earlier 66-byte shared-BX body
remains the useful isolated hypothesis. No production budget or admission
was claimed for this probe.
