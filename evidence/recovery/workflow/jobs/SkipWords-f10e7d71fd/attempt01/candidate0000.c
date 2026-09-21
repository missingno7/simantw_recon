/*
 * SkipWords: consume `count` whitespace-delimited words from a file
 * descriptor, using the same one-byte read loop as the admitted ReadWord.
 * For each word a far pointer is set to a local buffer (SS-based), leading
 * whitespace is skipped by reading single characters while isspace holds,
 * then characters are stored until end of file or the next whitespace,
 * and the buffer is terminated.  The count is post-decremented in place.
 */
extern int far read(int fd, void far *buffer, unsigned int count);
extern int far isspace(int character);

void far SkipWords(int fd, int count)
{
    char c;
    char far *p;
    char buffer[30];

    while (count--) {
        p = buffer;
        while (read(fd, &c, 1) && isspace(c))
            ;
        do {
            *p++ = c;
        } while (read(fd, &c, 1) && !isspace(c));
        *p = 0;
    }
}
