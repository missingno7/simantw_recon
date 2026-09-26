/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3966] -> ListIndexR, match_position[0x4078] -> ListIndexA, match_position[0x4cea] -> ListIndexB (one selector word per symbol in the object).
 *
 * SetAntIndex: write one ant list record's five fields (life, column,
 * attribute, state, direction) at a given index, bounds-checked against
 * 0 <= index < the list's live count in the named list-index word, twin write-side
 * of FindAntIndex and using the same field layout evidenced by
 * src/recovered/wf_AddAntToBList-e7a166edf6.c,
 * wf_AddAntToRList-63e08ccbad.c and wf_CompactListA-2c6f7e42f7.c. list <=
 * 1 selects the A-list (ListIndexA count; life 0x23a4,
 * column 0x278e, attribute 0x2f62, state 0x2b78, direction 0x334c),
 * list == 2 selects the B-list (ListIndexB count; life
 * 0x3736, column 0x392c, attribute 0x3d18, state 0x3b22, direction
 * 0x3f0e), otherwise the R-list (ListIndexR count; life
 * 0x4104, column 0x42fa, attribute 0x46e6, state 0x44f0, direction
 * 0x48dc). Out-of-range writes are silently dropped.
 */
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char far Dx8[];

void far SetAntIndex(int list, int index, int life, int column,
                      int attribute, int state, int direction)
{
    if (list <= 1) {
        if (index < 0 || index >= ListIndexA)
            return;
        Dx8[index + 0x23a4] = (unsigned char)life;
        Dx8[index + 0x278e] = (unsigned char)column;
        Dx8[index + 0x2f62] = (unsigned char)attribute;
        Dx8[index + 0x2b78] = (unsigned char)state;
        Dx8[index + 0x334c] = (unsigned char)direction;
    } else if (list == 2) {
        if (index < 0 || index >= ListIndexB)
            return;
        Dx8[index + 0x3736] = (unsigned char)life;
        Dx8[index + 0x392c] = (unsigned char)column;
        Dx8[index + 0x3d18] = (unsigned char)attribute;
        Dx8[index + 0x3b22] = (unsigned char)state;
        Dx8[index + 0x3f0e] = (unsigned char)direction;
    } else {
        if (index < 0 || index >= ListIndexR)
            return;
        Dx8[index + 0x4104] = (unsigned char)life;
        Dx8[index + 0x42fa] = (unsigned char)column;
        Dx8[index + 0x46e6] = (unsigned char)attribute;
        Dx8[index + 0x44f0] = (unsigned char)state;
        Dx8[index + 0x48dc] = (unsigned char)direction;
    }
}
