/*
 * The tree tables use 0x1000 as their unused-node sentinel.  The first far
 * table has 0x100 entries; the second is indexed by the 12-bit map space and
 * has 0x1000 entries.  Historical MSC optimizes these counted stores to the
 * two REP STOSW sequences shown in the target.
 */
struct TreeData {
    unsigned int roots[0x100];
    unsigned int links[0x1000];
};

extern struct TreeData far treeData;

void InitTree(void)
{
    int i;
    int j;

    for (i = 0; i < 0x100; ++i)
        treeData.roots[i] = 0x1000;
    for (j = 0; j < 0x1000; ++j)
        treeData.links[j] = 0x1000;
}
