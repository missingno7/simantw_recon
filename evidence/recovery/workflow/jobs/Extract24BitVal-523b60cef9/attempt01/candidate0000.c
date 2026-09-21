/*
 * Extract24BitVal: read a big-endian 24-bit value from a byte stream held
 * as far positions.  The destination long is cleared, its upper three
 * bytes (address formed with 32-bit arithmetic on the far pointer: add bx,1
 * / adc ax,0) receive three bytes copied from the far address held in the
 * source position (inline movsw/movsb with DS switched), the long is byte
 * swapped with the verified far FlipLong, and the source position advances
 * by three while the remaining count drops by three (both as 32-bit
 * add/sub with carry on memory).
 */
extern unsigned long far FlipLong(unsigned long value);
extern void far *far _fmemcpy(void far *dst, const void far *src, unsigned int n);

void far Extract24BitVal(long far *src, unsigned long far *value,
                         long far *remaining)
{
    *value = 0;
    _fmemcpy((char far *)((long)value + 1), (char far *)*src, 3);
    *value = FlipLong(*value);
    *src += 3;
    *remaining -= 3;
}
