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

    LifeA[(((unsigned short far *)(Dx8 + 0x23a4))[index] & 0x00ff) * 64 + Dx8[index + 0x278e]] = 0;
    countPtr = &match_position[0x4078];
    if (*countPtr <= 0)
        return;
    --*countPtr;
    count = *countPtr - index;
    BlockMove(&Dx8[index + 1 + 0x23a4], &Dx8[index + 0x23a4], count);
    BlockMove(&Dx8[index + 1 + 0x278e], &Dx8[index + 0x278e], count);
    BlockMove(&Dx8[index + 1 + 0x2b78], &Dx8[index + 0x2b78], count);
    BlockMove(&Dx8[index + 1 + 0x2f62], &Dx8[index + 0x2f62], count);
    BlockMove(&Dx8[index + 1 + 0x334c], &Dx8[index + 0x334c], count);
}
