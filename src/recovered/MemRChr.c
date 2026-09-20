unsigned char far *MemRChr(unsigned char far *buffer, int value,
                            unsigned int count)
{
    while (count) {
        --count;
        if (buffer[count] == (unsigned char)value)
            return buffer + count;
    }
    return 0;
}
