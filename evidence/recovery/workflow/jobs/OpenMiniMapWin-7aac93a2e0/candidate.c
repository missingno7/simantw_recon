/*
 * Evidence-backed reconstruction outline for OpenMiniMapWin(int x, int y).
 * This is preserved as research source, not submitted for strict testing:
 * two same-segment helper bodies and their unit placement are unresolved.
 *
 * The target and adjacent mini-map routines establish this setup:
 *
 *     savedPause = GamePaused;
 *     miniXSize = miniYSize = (displayType & 1) ? 2 : 1;
 *     win_Open(0x1400, x, y);
 *     MySetCapture(win_hwnd[20]);
 *     Mini_DrawMapI();
 *     miniMapCursorRect.top = miniYSize * MapPnt.y + miniMapRect.top;
 *     miniMapCursorRect.bottom = miniMapCursorRect.top +
 *                                miniYSize * editHeight;
 *     miniMapCursorRect.left = miniXSize * MapPnt.x + miniJust +
 *                              miniMapRect.left;
 *     miniMapCursorRect.right = miniMapCursorRect.left +
 *                               miniXSize * editWidth;
 *
 * It then inverts that rectangle and marks mmapCursorState visible. The
 * immediate-button path checks a mouse point against miniMapCursorRect and
 * can close the mini-map before calling OpenMapYard. The paused path pumps
 * win_GetEvent while window 0x1400 remains open; mouse coordinates are
 * converted with ScreenToClient, checked against miniMapRect, scaled by
 * miniXSize/miniYSize, range-checked against multiplier, and adjusted by
 * 0x20 for the 0x40-scale mode. A changed map point erases/redraws the
 * cursor and inverts the selection rectangle. On close it releases capture,
 * flushes events, and restores the saved pause state.
 *
 * Both this function and MapAreaEvent call the same private near routine at
 * ANTEDIT_MODULE:0x11620 with two coordinates, test its result, and then call
 * another private near routine at :0x111e0 with no arguments. MAPSYM does
 * not name either helper, and the available packets do not include their
 * bodies. Replacing either with an invented external or an empty helper
 * would not be evidence-backed source. The shared ANTEDIT_MODULE context
 * must recover both helpers and their selector/data ordering before a full
 * candidate can be tested.
 */
