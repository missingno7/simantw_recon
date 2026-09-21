/*
 * Hypothesis: the private fifteen-word rain array occupies the fixed
 * interval scanned by the target, from its first word through its fifteenth.
 * The routine counts leading -1 entries; an entirely exhausted array is
 * rejected.  Otherwise it prints the caller's far label, every array word,
 * and a trailing newline using the three strings recovered from CONST.
 */
static int rainArray[15];
extern void far WinPrintf(char far *format, ...);

int far CheckRainArray(char far *label)
{
    int count;
    int *cursor;

    count = 0;
    cursor = rainArray;
    while (*cursor == -1) {
        ++count;
        ++cursor;
        if (cursor > &rainArray[14])
            break;
    }
    if (count > 14)
        return 0;

    WinPrintf("%s", label);
    cursor = rainArray;
    do {
        WinPrintf("(%d)", *cursor);
        ++cursor;
    } while (cursor <= &rainArray[14]);
    WinPrintf("\n");
    return 1;
}
