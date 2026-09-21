/*
 * Append one byte to the active packed-output block.  The private cursor is
 * a far pointer split into offset and selector words; when the block count
 * reaches its limit, the next block is installed and the indirect pack flush
 * helper receives the completed count and new far-buffer pointer.
 */
extern unsigned char far *PackBuffer;
extern unsigned int PackWriteCount;
extern unsigned int PackWriteLimit;
extern unsigned char far *PackNextBuffer;
extern void (far *PackFlush)(unsigned int count, unsigned char far *buffer);

void PackWriteByte(unsigned char value)
{
    *PackBuffer++ = value;
    ++PackWriteCount;
    if (PackWriteCount >= PackWriteLimit) {
        PackBuffer = PackNextBuffer;
        PackFlush(PackWriteCount, PackBuffer);
        PackWriteCount = 0;
    }
}
