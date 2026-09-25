/* Expand each packed source byte through the four-entry monochrome-to-Tandy map. */
static const unsigned char monoToTandy[4] = { 0x75, 0x0b, 0x6a, 0x00 };
void far ConvertMonoToTandy(unsigned char far *destination,
                            unsigned char far *source,
                            unsigned int rowWidth, unsigned int rows)
{
    unsigned int bytesPerRow;
    unsigned char value;
    bytesPerRow = (rowWidth + 1) >> 1;
    do {
        unsigned int remaining = bytesPerRow;
        do {
            value = *source++;
            *destination++ = monoToTandy[value >> 6];
            *destination++ = monoToTandy[(value >> 4) & 3];
            *destination++ = monoToTandy[(value >> 2) & 3];
            *destination++ = monoToTandy[value & 3];
        } while (--remaining);
    } while (--rows);
}
