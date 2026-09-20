/*
 * The animation list is a far array of 0x2c-byte records.  FindObject walks
 * it from element zero while the caller-supplied far count remains positive,
 * comparing each record's word at offset 0x20 with the requested object
 * number.  On a match it stores the zero-based index through the far output
 * pointer and returns the matching record pointer; an empty or exhausted list
 * returns a null far pointer.  The target's LDS/LES instructions show that
 * both count and result-index arguments are far pointers.
 */
struct HanimObject {
    unsigned char prefix[0x20];
    int objectNumber;
    unsigned char suffix[0x0a];
};

struct HanimObject far *_hanim_FindObject(
    struct HanimObject far *objects,
    int far *count,
    int objectNumber,
    int far *foundIndex)
{
    int index;

    index = 0;
    if (*count > 0) {
        while (index < *count) {
            if (objects->objectNumber == objectNumber) {
                *foundIndex = index;
                return objects;
            }
            objects = (struct HanimObject far *)
                ((unsigned char far *)objects + 0x2c);
            ++index;
        }
    }
    return (struct HanimObject far *)0;
}
