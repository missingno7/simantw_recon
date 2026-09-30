# p4-redraw-gdi report

## Open questions that affect the SDL host

- **UNKNOWN - coordinate origin and edge convention.** The Win16 draw calls use a current HWND/DC and logical object rectangles, while the DOS path clips a framebuffer/window stack. Confirm whether every `win_GetObjRect`/`clip_SetWin` coordinate is already window-local or whether the drawing backend applies an origin before each primitive. Also confirm inclusive versus half-open rectangle edges for the low-level operations. SDL needs one stable conversion rule for child-window coordinates.
- **UNKNOWN - map cache ownership.** `editBuf` is clearly a retained CPU-side edit canvas. The exact ownership, format, invalidation points, and release path for `mapBuf` and `lastMapMapBuf` need a full call/use trace before deciding which SDL surfaces can persist across frames.
- **UNKNOWN - erase ordering.** The Win16 edit path validates the exposed region, updates remaining damage, then re-invalidates the exposed part after scroll. Determine whether SDL should preserve the same two-stage ordering or can combine it into one dirty-region redraw without changing map/cursor overlap.
- **UNKNOWN - background erase.** `MAINWNDPROC` is open and its best draft has no explicit `WM_ERASEBKGND` case. Verify the registered class background brush/default-procedure behavior for `InvalidateRect(..., TRUE)` so SDL can match when a damaged client area is cleared before SimAnt redraws it.
- **UNKNOWN - palette event equivalent.** Win16 redraws every visible child after a successful `RealizePalette` in `WM_QUERYNEWPALETTE`/active `WM_PALETTECHANGED`. The SDL port uses DOS palette/resources, so establish whether any runtime palette mutation remains in the DOS authority or whether these messages collapse to an ordinary full-window invalidation.
- **UNKNOWN - native versus logical chrome.** The main top-level frame is USER-owned; DOS draws custom window gadgets through `win_DrawWindow`, and Win16 `win_DrawTitle` feeds USER via `SetWindowText`. For each logical window flag, verify which border/title/menu elements are native chrome and which are client-area SimAnt objects before mapping them to separate SDL windows.
- **UNKNOWN - direct draw scheduling.** Exact `MSClipStart/End` wrappers acquire a DC outside `WM_PAINT`; editor graphs and transient cursor work use that path. Inventory which overlays rely on immediate visibility so the SDL host can schedule renderer updates without losing or duplicating work on expose.

## Evidence limits

- `MAINWNDPROC` and Win16 `_win_DrawWindow` remain open. The section labels their body-level claims `INFERRED`; the native imports, target addresses, `PaintStuff`, `RedrawWindows`, and `MYENUMFUNC` source are direct evidence.
- The DOS checkout was read only. No byte-matching, promotion, compiler, or validation tools were run.
