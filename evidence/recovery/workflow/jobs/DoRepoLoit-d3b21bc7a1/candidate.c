/*
 * Hypothesis: choose the random-ant or nest-ant routine from SRand2, then
 * inspect the selected Dx8 record.  A high bit in field 0x2f62 enables the
 * list-count checks; when the observed secondary count is above 100, mark
 * the record's 0x2b78 field with 0x0f.  The first count read is retained as
 * a source-level no-op because the target contains its compare followed by
 * an unconditional jump.
 */
extern int far SRand2(void);
extern void near DoRandAntAA(int index);
extern void near DoToNestAnt(int index);
extern unsigned char far Dx8[];
extern int far match_position[];

void near DoRepoLoit(int index)
{
    unsigned char far *list;

    if (SRand2())
        DoRandAntAA(index);
    else
        DoToNestAnt(index);

    list = Dx8;
    if ((list[index + 0x2f62] & 0x80) == 0)
        return;

    if (match_position[0x403c] > 100) {
        /* The target immediately transfers to the second count check. */
    }
    if (match_position[0x3e22] > 100)
        list[match_position[0x4db5] + 0x2b78] = 0x0f;
}
