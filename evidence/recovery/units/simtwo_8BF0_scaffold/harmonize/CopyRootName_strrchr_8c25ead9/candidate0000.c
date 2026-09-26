/*
 * Hypothesis: copy a bounded far filename, strip leading dots for the
 * extension search, and remove the final extension only when its dot occurs
 * after the final backslash.  The far library prototypes preserve the target
 * five-word strncpy and three-word strrchr call layouts.
 */
extern char far *strncpy(char far *dest, char far *src, unsigned int count);
extern char far * far strrchr(const char far *s, int ch);

void far CopyRootName(char far *dest, char far *src)
{
    char far *dot;

    strncpy(dest, src, 0x4f);
    dest[0x4f] = 0;

    if (*dest == '.') {
        do {
            ++dest;
        } while (*dest == '.');
    }

    dot = strrchr(dest, '.');
    if (dot != 0) {
        if (strrchr(dest, '\\') < dot)
            *dot = 0;
    }
}
