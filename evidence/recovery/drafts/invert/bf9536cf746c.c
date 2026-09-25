/* Complement bytes through a register-qualified far cursor with post-test count. */
void far invert(unsigned char far *buffer, unsigned int count)
{
    register unsigned char far *cursor = buffer;
    do {
        *cursor = (unsigned char)~*cursor;
        ++cursor;
    } while (--count);
}
