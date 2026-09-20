/*
 * The tree tables use 0x1000 as their unused-node sentinel.  The first far
 * table has 0x100 entries; the second is indexed by the 12-bit map space and
 * has 0x1000 entries.  Historical MSC optimizes these counted stores to the
 * two REP STOSW sequences shown in the target.
 */
extern unsigned int huge TreeTable[0x1100];

void InitTree(void)
{
    int i;

    for (i = 0; i < 0x100; ++i)
        TreeTable[i] = 0x1000;
    for (i = 0; i < 0x1000; ++i)
        TreeTable[i + 0x100] = 0x1000;
}
