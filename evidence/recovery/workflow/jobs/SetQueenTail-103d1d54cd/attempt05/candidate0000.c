/*
 * SetQueenTail installs a queen-tail life entry.  The requested life type
 * 0xff is the historical shorthand for 0xfe.  The table index is adjusted
 * in its low byte, then reused to index the object's two per-context
 * coordinate-offset far arrays Dx8/Dy8 (the same tables MoveMyLife adds
 * to x/y in this unit), whose sum with the caller's X/Y is sent to the
 * same-segment SetLife helper.
 */
extern char far Dy8[];
extern char far Dx8[];
extern void far SetLife(int plane, int x, int y, int type);

void SetQueenTail(int kind, int x, int y, int tableIndex, int tableType)
{
    int lifeType;

    if (tableType == 0xff)
        lifeType = 0xfe;
    else
        lifeType = tableType;

    tableIndex ^= 4;
    SetLife(kind, x + Dx8[tableIndex], y + Dy8[tableIndex], lifeType);
}
