/*
 * The LZSS encoder's current match position and match length are consecutive
 * 16-bit fields in PACK.  The recovered callers declare both as far integers;
 * their original initialized values are zero.
 */
int __based(__segname("PACK")) match_position = 0;
int __based(__segname("PACK")) match_length = 0;
