/*
 * SpecialTutorialInit: recognise the tutorial game file.  The file name's
 * base name (after the last backslash, or the whole name) is compared
 * case-insensitively with the first far MiscStrs string.  On a match the
 * tutorial is generated, the edit window is titled "Tutorial Game", the
 * simulation variables and random seed are initialised and the message
 * editor is opened at the origin with mode 1; otherwise the base name
 * itself becomes the edit window title.  Returns whether it matched.
 */
extern char far * far * far MiscStrs;

extern char far * far strrchr(const char far *text, int character);
extern int far stricmp(const char far *a, const char far *b);
extern void far GenerateTutorial(void);
extern void far SetEditWinTitle(long title);
extern void far InitSimVars(void);
extern void far SeedSRand(void);
extern void far EditMessage(long position, int a, int b, int mode);

int far SpecialTutorialInit(char far *name)
{
    char far *base;
    int tutorial;

    base = strrchr(name, 0x5c);
    if (base)
        base++;
    else
        base = name;
    tutorial = stricmp(base, MiscStrs[0]) == 0;
    if (tutorial) {
        GenerateTutorial();
        SetEditWinTitle((long)"Tutorial Game");
        InitSimVars();
        SeedSRand();
        EditMessage(0L, -2, -1, 1);
    } else
        SetEditWinTitle((unsigned long)base);
    return tutorial;
}
