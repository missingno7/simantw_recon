/*
 * Paired x/y coordinate series for the four numbered A/B motion profiles.
 * Each table keeps its original four word entries and profile order.
 */
int __based(__segname("SIMANT_DATA_GROUP")) L1xA[4] = { 0x0f0e, 0x0c0e, 0x0a0a, 0x0d0b };
int __based(__segname("SIMANT_DATA_GROUP")) L1xB[4] = { 0x1615, 0x1716, 0x1417, 0x1212 };
int __based(__segname("SIMANT_DATA_GROUP")) L2xA[4] = { 0x0d0e, 0x110e, 0x1213, 0x0f10 };
int __based(__segname("SIMANT_DATA_GROUP")) L2xB[4] = { 0x2123, 0x2020, 0x2222, 0x2322 };
int __based(__segname("SIMANT_DATA_GROUP")) L3xA[4] = { 0x0d0e, 0x100e, 0x0e10, 0x0e0c };
int __based(__segname("SIMANT_DATA_GROUP")) L3xB[4] = { 0x2121, 0x2121, 0x1e1e, 0x211f };
int __based(__segname("SIMANT_DATA_GROUP")) L4xA[4] = { 0x0d0b, 0x090b, 0x0808, 0x0a09 };
int __based(__segname("SIMANT_DATA_GROUP")) L4xB[4] = { 0x1617, 0x1513, 0x1716, 0x1717 };
int __based(__segname("SIMANT_DATA_GROUP")) L1yA[4] = { 0xf0ed, 0xf3f2, 0xf3f4, 0xeef0 };
int __based(__segname("SIMANT_DATA_GROUP")) L1yB[4] = { 0xdad6, 0xe2de, 0xe1e6, 0xd7db };
int __based(__segname("SIMANT_DATA_GROUP")) L2yA[4] = { 0xf9f8, 0xfbfb, 0xfaf8, 0xf9fa };
int __based(__segname("SIMANT_DATA_GROUP")) L2yB[4] = { 0xf5f6, 0xe9ef, 0xeae6, 0xf2ee };
int __based(__segname("SIMANT_DATA_GROUP")) L3yA[4] = { 0x0201, 0x0203, 0xff01, 0x00ff };
int __based(__segname("SIMANT_DATA_GROUP")) L3yB[4] = { 0x0602, 0x0e0a, 0x070c, 0xfe01 };
int __based(__segname("SIMANT_DATA_GROUP")) L4yA[4] = { 0x0a09, 0x080b, 0x0406, 0x0706 };
int __based(__segname("SIMANT_DATA_GROUP")) L4yB[4] = { 0x201c, 0x181f, 0x1013, 0x1814 };
