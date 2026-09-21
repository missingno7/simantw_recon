/* TERRAINset at PACK:9B6E selects tile band 48..4B when zero and 18..27 otherwise. NE selector C320 resolves PACK, not the Dx8 segment. */
extern unsigned int far TERRAINset;

int IsItFood(int tile)
{
    if (TERRAINset == 0) {
        if (tile < 0x48 || tile > 0x4b)
            return 0;
        return 1;
    }
    if (tile < 0x18 || tile > 0x27)
        return 0;
    return 1;
}
