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
    char far *dot;
    char near *scan;

    strncpy(dest, src, 0x4f);
    dest[0x4f] = 0;

    scan = (char near *)dest;
    if (*scan == '.') {
        do {
            ++scan;
        } while (*scan == '.');
    }

    dot = strrchr((char far *)scan, '.');
    if (dot != 0) {
        if (strrchr((char far *)scan, '\\') < dot)
            *dot = 0;
    }
}
