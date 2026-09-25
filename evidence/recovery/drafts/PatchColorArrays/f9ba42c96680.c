/*
 * PatchColorArrays: remap SimAnt's stored VGA palette-index tables
 * (CTab, HTab, LTab, CTabB, CTabR, PherColorTab) through a fixed
 * 16-entry color-index conversion table.  Every byte in every table is
 * replaced with table[byte].  CTabB and CTabR are the same length and
 * are patched together in one loop; the others each get their own loop.
 */
extern unsigned char near CTab[144];
extern unsigned char near HTab[208];
extern unsigned char near LTab[32];
extern unsigned char near CTabB[24];
extern unsigned char near CTabR[24];
extern unsigned char near PherColorTab[16];

void far PatchColorArrays(void)
{
    unsigned char table[16] = {15, 11, 2, 9, 14, 5, 4, 12, 2, 10, 7, 3, 6, 8, 7, 0};
    int i;

    for (i = 0; i < 144; i++)
        CTab[i] = table[CTab[i]];
    for (i = 0; i < 208; i++)
        HTab[i] = table[HTab[i]];
    for (i = 0; i < 32; i++)
        LTab[i] = table[LTab[i]];
    for (i = 0; i < 24; i++) {
        CTabB[i] = table[CTabB[i]];
        CTabR[i] = table[CTabR[i]];
    }
    for (i = 0; i < 16; i++)
        PherColorTab[i] = table[PherColorTab[i]];
}
