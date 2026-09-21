/*
 * Extract24BitVal: read a big-endian 24-bit value from a byte stream.  The
 * destination long is cleared, then its upper three bytes (address formed
 * with 32-bit arithmetic on the far pointer, as in the verified ExtractWord
 * cursor idiom) receive a three-byte structure copied from the far cursor
 * position; the compiler emits the copy inline as movsw/movsb with DS
 * switched, as in the admitted win_GetObjRect rectangle copy.  The long is
 * byte swapped with the verified far FlipLong, the cursor advances by
 * three through the same unsigned-long idiom, and the remaining count
 * drops by three.
 */
struct ThreeBytes {
    unsigned char b[3];
};

extern unsigned long far FlipLong(unsigned long value);

void far Extract24BitVal(void far * far *cursor, unsigned long far *value,
                         long far *remaining)
{
    *value = 0;
    *(struct ThreeBytes far *)((unsigned long)value + 1) =
        *(struct ThreeBytes far *)*cursor;
    *value = FlipLong(*value);
    *cursor = (void far *)((unsigned long)*cursor + 3);
    *remaining -= 3;
}
