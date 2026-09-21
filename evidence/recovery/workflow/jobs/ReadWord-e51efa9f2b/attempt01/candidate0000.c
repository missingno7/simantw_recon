/*
 * Hypothesis: read one byte at a time from fd, discard leading whitespace,
 * copy the first word into the caller's far buffer, and terminate it at the
 * first later whitespace or at read exhaustion.
 */
extern int far read(int fd, void far *buffer, unsigned int count);
extern int far isspace(int character);

void far ReadWord(int fd, char far *buffer)
{
    char character;

    for (;;) {
        if (read(fd, &character, 1) == 0)
            break;
        if (!isspace(character))
            break;
    }
    for (;;) {
        *buffer++ = character;
        if (read(fd, &character, 1) == 0)
            break;
        if (isspace(character))
            break;
    }
    *buffer = 0;
}
