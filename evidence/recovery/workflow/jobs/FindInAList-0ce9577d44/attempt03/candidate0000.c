/*
 * FindInAList searches the active A-list from its last occupied slot toward
 * zero.  The list index is the byte offset into the Dx8 record area.  A slot
 * is eligible when its two one-byte keys equal the two arguments and its
 * removal/occupancy byte is nonzero; the first eligible index is returned
 * and an empty or exhausted list returns -1.
 *
 * The selector at AListState[0x80f0] is the private list-count word observed
 * in the target ES load.  Dx8's three fields are at the target record
 * displacements 0x23a4, 0x278e, and 0x2f62.
 */
extern unsigned int far *AListState;
extern unsigned char far Dx8[];

int FindInAList(int firstKey, int secondKey)
{
    int index;

    index = AListState[0x4078];
    while (index > 0) {
        --index;
        if (Dx8[index + 0x23a4] == firstKey &&
            Dx8[index + 0x278e] == secondKey &&
            Dx8[index + 0x2f62] != 0)
            return index;
    }
    return -1;
}
