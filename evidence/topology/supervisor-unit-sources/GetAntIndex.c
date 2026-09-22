/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3966] -> ListIndexR, match_position[0x4078] -> ListIndexA, match_position[0x4cea] -> ListIndexB (one selector word per symbol in the object).
 *
 * GetAntIndex: read one ant list record's five fields (life, column,
 * attribute, state, direction) at a given index, bounds-checked against
 * 0 <= index < the list's live count in match_position, read side of
 * SetAntIndex/FindAntIndex/FindLifeIndex and using the same field
 * layout evidenced by src/recovered/wf_AddAntToBList-e7a166edf6.c,
 * wf_AddAntToRList-63e08ccbad.c and wf_CompactListA-2c6f7e42f7.c. list
 * <= 1 selects the A-list (ListIndexA count; life 0x23a4,
 * column 0x278e, attribute 0x2f62, state 0x2b78, direction 0x334c),
 * list == 2 selects the B-list (ListIndexB count; life
 * 0x3736, column 0x392c, attribute 0x3d18, state 0x3b22, direction
 * 0x3f0e), otherwise the R-list (ListIndexR count; life
 * 0x4104, column 0x42fa, attribute 0x46e6, state 0x44f0, direction
 * 0x48dc). Each field is written through a far output pointer. Returns
 * true on success, false when the index is out of range. Dx8 is
 * addressed as a scalar far byte (SetAntIndex's array-index reads
 * compiled fine as writes, but the same array form compiled as a
 * relocatable fixup for these reads; the AT() macro used by
 * FixExitMapB/R avoids that here too).
 */
extern int far match_position[];
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])

int far GetAntIndex(int list, int index, int far *life, int far *column,
                     int far *attribute, int far *state, int far *direction)
{
    if (list <= 1) {
        if (index < 0 || index >= ListIndexA)
            return 0;
        *life = AT(index + 0x23a4);
        *column = AT(index + 0x278e);
        *attribute = AT(index + 0x2f62);
        *state = AT(index + 0x2b78);
        *direction = AT(index + 0x334c);
    } else if (list == 2) {
        if (index < 0 || index >= ListIndexB)
            return 0;
        *life = AT(index + 0x3736);
        *column = AT(index + 0x392c);
        *attribute = AT(index + 0x3d18);
        *state = AT(index + 0x3b22);
        *direction = AT(index + 0x3f0e);
    } else {
        if (index < 0 || index >= ListIndexR)
            return 0;
        *life = AT(index + 0x4104);
        *column = AT(index + 0x42fa);
        *attribute = AT(index + 0x46e6);
        *state = AT(index + 0x44f0);
        *direction = AT(index + 0x48dc);
    }
    return 1;
}
