/*
 * RecruitRed: switch up to `count` idle red ants in the A list into
 * recruiting mode.  ListIndexA (far, segment-9 selector slot 0xc4d2) bounds
 * the list; the list bytes live in the selected SIMANT_DATA_GROUP (Dx8)
 * segment, walked with DS switched as in the verified ClearLifeB/FindInBList
 * sources: AlistT at 0x2f62 (type byte, red when above 0x7f, mode in bits
 * 3..6), AlistM at 0x2b78 (current mode) and AlistS at 0x334c (stamina).
 * Walking the list from the top while ants remain and recruits are still
 * needed, a live red ant whose type mode is 2 or 6 and whose current mode
 * is neither 0x13 nor 6 is set to mode 6 with zero stamina, and the
 * remaining count (a local copy of the argument) is decremented.  The
 * current mode byte is fetched through a far pointer to the element whose
 * segment the compiler already holds in DS, so only the offset is formed
 * in BX before the load; it is read before the type mode is extracted.
 */
extern int far ListIndexA;
extern unsigned char far Dx8[];

void far RecruitRed(int count)
{
    int cur;
    int need;
    int i;
    int type;
    int mode;

    need = count;
    i = ListIndexA;
    while (i > 0 && need > 0) {
        i--;
        type = Dx8[i + 0x2f62];
        if (type != 0 && type > 0x7f) {
            cur = *(&Dx8[0x2b78] + i);
            mode = (type & 0x78) >> 3;
            if (mode == 2 || mode == 6) {
                if (cur != 0x13 && cur != 6) {
                    Dx8[i + 0x2b78] = 6;
                    Dx8[i + 0x334c] = 0;
                    need--;
                }
            }
        }
    }
}
