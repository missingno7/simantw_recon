/*
 * Hypothesis: copy a bounded far filename, strip leading dots for the
 * extension search, and remove the final extension only when its dot occurs
 * after the final backslash.  The far library prototypes preserve the target
 * five-word strncpy and three-word strrchr call layouts.
 */
extern char far *strncpy(char far *dest, char far *src, unsigned int count);
extern char far *strrchr(char far *text, int ch);

void far CopyRootName(char far *dest, char far *src)
{
    char far *scan;
    char far *dot;
    char far *slash;

    strncpy(dest, src, 0x4f);
    dest[0x4f] = 0;

    scan = dest;
    if (*scan == '.') {
        do {
            ++scan;
        } while (*scan == '.');
    }

    dot = strrchr(scan, '.');
    if (dot != 0) {
        slash = strrchr(scan, '\\');
        if (slash < dot)
            *dot = 0;
    }
}
