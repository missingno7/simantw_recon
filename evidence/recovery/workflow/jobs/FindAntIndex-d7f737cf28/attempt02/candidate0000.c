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
 * the list is exhausted without a match. Each field is addressed through
 * its own far Dx8-relative pointer local, one per record field, matching
 * the three independent segment/offset contexts observed in the target.
 */
extern int far match_position[];
extern unsigned char far Dx8[];

int far FindAntIndex(int list, int life, int column, int attribute)
{
    unsigned char far *lifeArr;
    unsigned char far *columnArr;
    unsigned char far *attrArr;
    int count;
    int i;

    if (list <= 1) {
        count = match_position[0x4078];
        lifeArr = Dx8 + 0x23a4;
        columnArr = Dx8 + 0x278e;
        attrArr = Dx8 + 0x2f62;
    } else if (list == 2) {
        count = match_position[0x4cea];
        lifeArr = Dx8 + 0x3736;
        columnArr = Dx8 + 0x392c;
        attrArr = Dx8 + 0x3d18;
    } else {
        count = match_position[0x3966];
        lifeArr = Dx8 + 0x4104;
        columnArr = Dx8 + 0x42fa;
        attrArr = Dx8 + 0x46e6;
    }
    for (i = count - 1; i >= 0; i--) {
        if (lifeArr[i] == life && columnArr[i] == column && attrArr[i] == attribute)
            break;
    }
    return i;
}
