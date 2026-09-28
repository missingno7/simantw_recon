/*
 * The SIMTWO LZSS encoder state in PACK.
 *
 * pack_buf is the text buffer: a 4096-byte circular input window followed by
 * 18 mirrored lookahead bytes (N + F - 1 = 4113, word-aligned to 0x1012).  Its
 * 12-bit cursor wraps within the window; the mirror writes reach PACK:1015h.
 *
 * The binary-search trees follow it in the classic LZSS layout:
 * lson[N + 1], rson[N + 257] and dad[N + 1], with N = 4096 and NIL = N.  The
 * admitted tree routines (DeleteNode) index them at PACK:1016h, 3018h and 521Ah
 * and compare against the NIL value 1000h.  They are private to the encoder
 * object; the next PACK contribution begins at 721Ch.
 */
unsigned char __based(__segname("PACK")) pack_buf[0x1012] = {0};
static int __based(__segname("PACK")) lson[4096 + 1] = {0};
static int __based(__segname("PACK")) rson[4096 + 257] = {0};
static int __based(__segname("PACK")) dad[4096 + 1] = {0};
