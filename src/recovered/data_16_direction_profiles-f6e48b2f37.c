/*
 * Base direction offsets followed by the four numbered A/B x/y coordinate
 * series.  Every table is kept as its original sequence of word entries.
 */
int __based(__segname("SIMANT_DATA_GROUP")) Dx[2] = { 0x0607, 0x0003 };
int __based(__segname("SIMANT_DATA_GROUP")) Dy[2] = { 0x0200, 0x0605 };
int __based(__segname("SIMANT_DATA_GROUP")) D1xA[4] = { 0x1516, 0x1113, 0x100f, 0x1512 };
int __based(__segname("SIMANT_DATA_GROUP")) D1yA[4] = { 0x00fd, 0x0000, 0xfeff, 0xfdfd };
int __based(__segname("SIMANT_DATA_GROUP")) D2xA[4] = { 0x0e10, 0x100d, 0x1113, 0x0f0f };
int __based(__segname("SIMANT_DATA_GROUP")) D2yA[4] = { 0x0404, 0x0907, 0x0808, 0x0507 };
int __based(__segname("SIMANT_DATA_GROUP")) D3xA[4] = { 0x0708, 0x0807, 0x0a09, 0x0908 };
int __based(__segname("SIMANT_DATA_GROUP")) D3yA[4] = { 0x0d0d, 0x0e0e, 0x0b0e, 0x0c0a };
int __based(__segname("SIMANT_DATA_GROUP")) D4xA[4] = { 0xfffe, 0x0100, 0x0000, 0x0000 };
int __based(__segname("SIMANT_DATA_GROUP")) D4yA[4] = { 0x0f12, 0x0b0c, 0x0f0d, 0x0e11 };
int __based(__segname("SIMANT_DATA_GROUP")) D1xB[4] = { 0x292c, 0x2427, 0x2322, 0x2926 };
int __based(__segname("SIMANT_DATA_GROUP")) D1yB[4] = { 0xf6f2, 0xfcf9, 0xf9ff, 0xf1f3 };
int __based(__segname("SIMANT_DATA_GROUP")) D2xB[4] = { 0x1e1f, 0x2722, 0x272a, 0x2225 };
int __based(__segname("SIMANT_DATA_GROUP")) D2yB[4] = { 0x1012, 0x070b, 0x0906, 0x0f0c };
int __based(__segname("SIMANT_DATA_GROUP")) D3xB[4] = { 0x1215, 0x0c0f, 0x0f0b, 0x1814 };
int __based(__segname("SIMANT_DATA_GROUP")) D3yB[4] = { 0x1d1b, 0x2320, 0x1c21, 0x1818 };
int __based(__segname("SIMANT_DATA_GROUP")) D4xB[4] = { 0xfcf6, 0x0300, 0xfd00, 0xf7fa };
int __based(__segname("SIMANT_DATA_GROUP")) D4yB[4] = { 0x2226, 0x1e1f, 0x2421, 0x2926 };
