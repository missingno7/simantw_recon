/*
 * GetAntIndex: read one ant list record's five fields (life, column,
 * attribute, state, direction) at a given index, bounds-checked against
 * 0 <= index < the list's live count in match_position, read side of
 * SetAntIndex/FindAntIndex/FindLifeIndex and using the same field
 * layout evidenced by src/recovered/wf_AddAntToBList-e7a166edf6.c,
 * wf_AddAntToRList-63e08ccbad.c and wf_CompactListA-2c6f7e42f7.c. list
 * <= 1 selects the A-list (match_position[0x4078] count; life 0x23a4,
 * column 0x278e, attribute 0x2f62, state 0x2b78, direction 0x334c),
 * list == 2 selects the B-list (match_position[0x4cea] count; life
 * 0x3736, column 0x392c, attribute 0x3d18, state 0x3b22, direction
 * 0x3f0e), otherwise the R-list (match_position[0x3966] count; life
 * 0x4104, column 0x42fa, attribute 0x46e6, state 0x44f0, direction
 * 0x48dc). Each field is written through a far output pointer. Returns
 * true on success, false when the index is out of range.
 */
extern int far match_position[];
extern unsigned char far Dx8[];

int far GetAntIndex(int list, int index, int far *life, int far *column,
                     int far *attribute, int far *state, int far *direction)
{
    if (index < 0)
        return 0;
    if (list <= 1) {
        if (index >= match_position[0x4078])
            return 0;
        *life = Dx8[index + 0x23a4];
        *column = Dx8[index + 0x278e];
        *attribute = Dx8[index + 0x2f62];
        *state = Dx8[index + 0x2b78];
        *direction = Dx8[index + 0x334c];
    } else if (list == 2) {
        if (index >= match_position[0x4cea])
            return 0;
        *life = Dx8[index + 0x3736];
        *column = Dx8[index + 0x392c];
        *attribute = Dx8[index + 0x3d18];
        *state = Dx8[index + 0x3b22];
        *direction = Dx8[index + 0x3f0e];
    } else {
        if (index >= match_position[0x3966])
            return 0;
        *life = Dx8[index + 0x4104];
        *column = Dx8[index + 0x42fa];
        *attribute = Dx8[index + 0x46e6];
        *state = Dx8[index + 0x44f0];
        *direction = Dx8[index + 0x48dc];
    }
    return 1;
}
