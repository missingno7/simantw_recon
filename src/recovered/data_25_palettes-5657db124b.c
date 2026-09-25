/* Three Win16 color lookup tables: EGA color values, RGB color values and
 * the ordered system-color indices used by the interface. */
unsigned long __based(__segname("SIMANT_DATA_GROUP")) egargb[16] = {
    0x00000000UL, 0x00aa0000UL, 0x0000aa00UL, 0x00aaaa00UL,
    0x000000aaUL, 0x00aa00aaUL, 0x000055aaUL, 0x00aaaaaaUL,
    0x00555555UL, 0x00ff5555UL, 0x0055ff55UL, 0x00ffff55UL,
    0x005555ffUL, 0x00ff55ffUL, 0x0055ffffUL, 0x00ffffffUL
};
unsigned long __based(__segname("SIMANT_DATA_GROUP")) rgb[16] = {
    0x00000000UL, 0x00000080UL, 0x00008000UL, 0x00008080UL,
    0x00800000UL, 0x00800080UL, 0x00808000UL, 0x00808080UL,
    0x00c0c0c0UL, 0x000000ffUL, 0x0000ff00UL, 0x0000ffffUL,
    0x00ff0000UL, 0x00ff00ffUL, 0x00ffff00UL, 0x00ffffffUL
};
unsigned int __based(__segname("SIMANT_DATA_GROUP")) sysColor[19] = {
    10, 2, 12, 1, 15, 16, 18, 9, 17, 13,
    14, 11, 3, 4, 7, 0, 5, 6, 8
};
