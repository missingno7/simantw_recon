# `_PlaceQueenInYard` semantic hypothesis

## Evidence

- The factory packet confirms a 937-byte `SIMANT_MODULE` extent under the assigned `baseline` MSC 7.00 profile (`/AL /G2 /Gs /Oelw`). Direct MAPSYM evidence identifies `QueenStorageB`, `CurGameType`, `LayDownQueenMode`, `CurYardPnt`, `mapTileRect`, `patchRgn`, `YMapPopB`, `BColoniesStarted`, and `ColonyUpdateFlag`.
- The packet's event path reads the 16-byte event object's `object` word at `+0x0c`; event object `0x1902` supplies a click point. Otherwise the body queries the mouse, converts it to client coordinates, and gates processing on `win_IsWinInFront(0x1900)`.
- The two unnamed same-segment near-call destinations normalize to `0001:0000` and `0001:0034`; MAPSYM identifies these as `_StopSimulation` and `_RestartSimulation`. Their admitted sources confirm the placement loop pauses simulation and restores it on exit.
- The screen-to-yard conversion in the disassembly is `(py - mapTileRect.top - patchRgn.y) / 10` for row, then `(row * 10 + px - mapTileRect.left - patchRgn.x) / 28` for column. This matches the yard cursor and `YardArea` source pattern in the existing antedit yard sources.
- The admitted `QueenBalloons` and `SetQueenTail` routines establish queen-point and queen-life context; the admitted yard sources establish cursor inversion and yard/map redraw conventions. `DoScenario` provides the verified 16-byte event layout with the object field at `+0x0c`.

## Reconstructed behavior

The routine refuses placement when `QueenStorageB < 1`, plays the failure sound, displays a prompt, and exits. It also has a distinct `CurGameType == 2` prompt/exit path. When `LayDownQueenMode == 1`, it clears that mode. It then derives a placement rectangle extending three yard cells around `CurYardPnt`, clamped to columns `0..11` and rows `0..15`.

The routine flushes events, presents the placement prompt, and tracks the current cursor cell using `-1` as the no-cell sentinel. It converts the click or current mouse point through `mapTileRect` and `patchRgn`, and inverts the previous/new yard cell under `MSClipStart`/`MSClipEnd`. A click inside the clamped rectangle plays song `0x2afb` at priority `0x7e`, decrements `QueenStorageB`, increments `YMapPopB[col][row]` and `BColoniesStarted`, sets `ColonyUpdateFlag` to `1`, calls `MakeDMap(1)` and `DrawMap`, then updates the yard or exits according to remaining queen storage.

## Remaining uncertainty

The high-level event-loop shape and transitions among cursor motion, invalid points, click placement, shift-key repeat, and exit still need to be checked against the target branches. A first strict test is useful to locate source-shape divergences; the candidate uses only packet-bound globals and identified calls.
