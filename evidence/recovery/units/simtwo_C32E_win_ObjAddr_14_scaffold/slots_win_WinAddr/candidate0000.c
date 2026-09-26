/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
extern void far * near win_handles[];
void far *win_WinAddr(int id) { return win_handles[id>>8]; }
