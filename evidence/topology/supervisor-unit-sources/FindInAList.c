/*
 * FindInAList searches the active A-list from its last occupied slot toward
 * zero.  The list index is the byte offset into the Dx8 record area.  A slot
 * is eligible when its two one-byte keys equal the two arguments and its
 * removal/occupancy byte is nonzero; the first eligible index is returned
 * and an empty or exhausted list returns -1.
 *
 * The list bound is the public ListIndexA (PACK 0x80F0), as in the admitted
 * FindInBList/FindInRList twins; the three Dx8 fields are AlistX (0x23a4),
 * AlistY (0x278e) and AlistT (0x2f62), spelled as record displacements like
 * the twins.  Unit review (simone:2B42): the earlier spelling bound the same
 * word through an invented array name.
 */
extern int far ListIndexA;
extern unsigned char far Dx8[];

int FindInAList(int firstKey, int secondKey)
{
    int index;

    index = ListIndexA;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x23a4] == firstKey &&
            Dx8[index + 0x278e] == secondKey &&
            Dx8[index + 0x2f62] != 0)
            return index;
    }
    return -1;
}
