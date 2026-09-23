# `_SpiderDialog` bounded investigation

Job `SpiderDialog-12e6d7a7b5` remains `MATCH_READY` only until the factory blocker is recorded. The target extent is confirmed at `SIMANT_MODULE:0x673A`, length 537 bytes. No strict exact source was found; no candidate was promoted.

## Established behavior

- Locks window object `0x1A00`, assigns bitmap `0x2EE0` to object `0x1A01`, opens the first object, captures `win_hwnd[42]`, and gets the second object's rectangle.
- Starts sound `(0x2D, 0, 0x7E)`, initializes dialog wait for 8 ticks, offsets rectangle left/top by `0x2E/0x4D`, and masks `monoPat` with `0x7F`.
- In the modal loop, abort/event ends the loop; each elapsed eight-tick interval advances animation frame 1–3, then resets to frame 0 and plays the sound. It clips around drawing `AnTab[frame] + 0x2EE1` at the adjusted rectangle and checks abort again.
- Finishes the dialog, chooses string resource `0x273F` or `0x2740` using `SRand1(2)`, optionally redraws the last bitmap, stops simulation, loads/counts the strings, displays `PictureDialog(strings,count,0,1)`, frees/purges the loaded resource, restarts simulation, flushes events, unlocks, restores or releases capture based on `IsWindowVisible`, closes the window, and updates all windows.

## Effective-output classes

Attempts 1–4 produced distinct objects, not strict matches. Attempt 1: 572-byte function contribution, 70 equal literal bytes; attempt 3: 570 bytes, 69 equal; attempt 4: 556 bytes, 67 equal. Attempt 2 had different source text but the same OMF as attempt 1 and was deduplicated. Attempts 5 and 7 were compile failures (attempt 5's union member typo; attempt 7's malformed aggregate declaration); neither produced an OMF.

Attempt 6 introduced a union reusing the long deadline slot for the later far-string pointer and register locals; it produced a 542-byte contribution with `enter 0x12`, 65 equal literal bytes, and 6/45 matching fixups. The final bounded probe repaired the intended aggregate local layout (`WinRect` followed by captured handle), preserving that 542-byte frame and improving literal equality to 66 bytes. Attempt 8's source/object hashes are `0fcf47ca133e…` / `604a27411e65…`; it remains `NO_COMPLETE_MATCH`. The readable attempt-8 source is left as `candidate.c`.

## Remaining blocker / discriminating question

Strict proof still reports 39 unresolved or mismatched `SIMANT_MODULE` fixups, uncovered loader relocations, literal differences, a conflicting private `CONST` placement, and an unplaced `CONST` contribution. `AnTab` is known to be MAPSYM segment 8 at offset `0x87FC`, but its candidate far reference creates the private selector-pool conflict. The isolated function also cannot establish all original object-level references from signatures alone.

Next discriminating experiment: build/test the owning `simant:673A` translation-unit context (with the evidenced `AnTab` pool slot and neighboring publics) and check whether the private selector pool and internal call relocations resolve to the target's identities. Only after that context is correct should source-shape work resume against the remaining body-byte differences.
