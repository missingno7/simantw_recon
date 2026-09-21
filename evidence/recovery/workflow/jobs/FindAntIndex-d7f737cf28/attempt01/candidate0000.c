/*
 * FindAntIndex: search one ant list's parallel record fields (stored in
 * the shared far Dx8 record segment, indexed by list, matching
 * src/recovered/wf_AddAntToBList-e7a166edf6.c, wf_AddAntToRList-63e08ccbad.c
 * and wf_CompactListA-2c6f7e42f7.c) for an entry whose life/column/
 * attribute fields equal the given triple, scanning from the newest
 * (highest index) entry down to 0. list <= 1 selects the A-list
 * (match_position[0x4078] count; life 0x23a4, column 0x278e, attribute
 * 0x2f62, matching CompactListA's field offsets), list == 2 selects the
 * B-list (match_position[0x4cea] count; life 0x3736, column 0x392c,
 * attribute 0x3d18, matching AddAntToBList), otherwise the R-list
 * (match_position[0x3966] count; life 0x4104, column 0x42fa, attribute
 * 0x46e6, matching AddAntToRList). Returns the matching index, or -1 when
 * the list is exhausted without a match.
 */
extern int far match_position[];
extern unsigned char far Dx8[];

int far FindAntIndex(int list, int life, int column, int attribute)
{
    int count;
    int lifeBase;
    int columnBase;
    int attributeBase;
    int i;

    if (list <= 1) {
        count = match_position[0x4078];
        lifeBase = 0x23a4;
        columnBase = 0x278e;
        attributeBase = 0x2f62;
    } else if (list == 2) {
        count = match_position[0x4cea];
        lifeBase = 0x3736;
        columnBase = 0x392c;
        attributeBase = 0x3d18;
    } else {
        count = match_position[0x3966];
        lifeBase = 0x4104;
        columnBase = 0x42fa;
        attributeBase = 0x46e6;
    }
    for (i = count - 1; i >= 0; i--) {
        if (Dx8[lifeBase + i] == life &&
            Dx8[columnBase + i] == column &&
            Dx8[attributeBase + i] == attribute)
            break;
    }
    return i;
}
