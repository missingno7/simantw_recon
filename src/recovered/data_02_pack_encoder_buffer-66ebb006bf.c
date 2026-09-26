/*
 * The SIMTWO encoder treats pack_buf as a 4096-byte circular input window
 * followed by 18 mirrored lookahead bytes.  Its 12-bit cursor wraps within
 * the window; the mirror writes reach PACK:1015h.  Since pack_buf begins at
 * PACK:0004h, this defines exactly the 4114 bytes touched by that algorithm.
 */
unsigned char __based(__segname("PACK")) pack_buf[0x1012] = {0};
