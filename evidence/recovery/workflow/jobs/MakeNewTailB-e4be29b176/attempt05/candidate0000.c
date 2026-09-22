/* MakeNewTailB(tail) grows a new tail segment behind ant "tail": reads its
 * BlistT attribute byte (Dx8[tail+0x3d18], exact MAPSYM name), computes
 * marker=attr+8 (the "new segment" id, same +8 convention as
 * LostTailB/KillTailB's headMarker/tailMarker) and dir=(attr&7)^4 (the
 * opposite-direction reversal from LostTailB), looks up the signed
 * X/Y deltas Dx8[dir]/Dy8[dir] (the shared direction-delta tables from
 * LostHeadB/R), and adds them to the ant's cached BlistY (Dx8[tail+0x392c],
 * exact MAPSYM name) and its cached row/X field (Dx8[tail+0x3736], the
 * same per-ant field KillTailB reads as "row" -- unsigned, zero-extended,
 * no exact MAPSYM name resolved for this one instance but the offset and
 * field width are already evidenced). Calls
 * AddAntToBList(newX, newY, marker, 9, 0) (5-arg signature from the
 * admitted src/recovered/wf_AddAntToList-44a11714fc.c). */

extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern void far AddAntToBList(int x, int y, int type, int a, int b);

void far MakeNewTailB(int tail)
{
    int attr;
    unsigned char dir;
    int marker;
    int newY;
    int newX;

    attr = Dx8[tail + 0x3d18];
    marker = attr + 8;
    dir = attr & 7;
    dir ^= 4;
    newY = (signed char)Dy8[dir] + Dx8[tail + 0x392c];
    newX = (signed char)Dx8[dir] + Dx8[tail + 0x3736];
    AddAntToBList(newX, newY, marker, 9, 0);
}
