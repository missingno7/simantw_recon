/*
 * RemoveFromAList: remove index from the A-list. Clears the near LifeA
 * tracking cell for that ant (row AlistX[index], column AlistY[index],
 * matching the exact MAPSYM names for the A-list's far record fields,
 * offsets 0x23a4/0x278e within the same combined Dx8 object used by
 * CompactListA/FindAntIndex/SetAntIndex/FindLifeIndex), then -- if the
 * list isn't already empty -- decrements match_position[0x4078] (the
 * A-list count) and shifts every entry after index down by one slot in
 * each of the five parallel field arrays (0x23a4, 0x278e, 0x2b78,
 * 0x2f62, 0x334c) via the far runtime helper BlockMove, matching
 * src/recovered/BlockMove.c's copy-loop semantics; the source at this
 * call site is a plain int subtraction promoted to a long count with no
 * prototype truncation, observed as a 32-bit (cdq-extended) argument.
 */
extern int far match_position[];
extern unsigned char far Dx8[];
extern unsigned char near LifeA[];

extern void far BlockMove(unsigned char far *source, unsigned char far *destination, long count);

void far RemoveFromAList(int index)
{
    long count;
    int far *countPtr;
    unsigned char far *base;

    LifeA[(Dx8[index + 0x23a4] << 6) + Dx8[index + 0x278e]] = 0;
    base = Dx8;
    countPtr = &match_position[0x4078];
    if (*countPtr <= 0)
        return;
    --*countPtr;
    count = *countPtr - index;
    BlockMove(base + 0x23a4 + index + 1, base + 0x23a4 + index, count);
    BlockMove(base + 0x278e + index + 1, base + 0x278e + index, count);
    BlockMove(base + 0x2b78 + index + 1, base + 0x2b78 + index, count);
    BlockMove(base + 0x2f62 + index + 1, base + 0x2f62 + index, count);
    BlockMove(base + 0x334c + index + 1, base + 0x334c + index, count);
}
