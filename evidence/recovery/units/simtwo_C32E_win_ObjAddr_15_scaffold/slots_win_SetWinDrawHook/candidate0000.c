/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
typedef void (far *Hook)(void);
extern Hook far win_drawHooks[];
void win_SetWinDrawHook(int id,Hook f) { win_drawHooks[id>>8]=f; }
