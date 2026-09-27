/* Rebuild the shared help path in a file-scope far buffer. */
extern unsigned int near hInst;
extern int far hHelpCursor;
extern char far * far helpFileName;
extern unsigned int far pascal LoadCursor(unsigned int instance, char far *name);
extern char far *getcwd(char far *buffer, int maxlen);
extern unsigned int strlen(const char far *s);
extern char far *strcat(char far *dest, const char far *src);
extern char __based(__segname("PACK")) GameTime[];
void far SetHelpCursor(void)
{
    unsigned int length;
    hHelpCursor = LoadCursor(hInst, "HelpCursor");
    getcwd(GameTime + 4, 0x100);
    length = strlen(GameTime + 4);
    if (GameTime[4 + length - 1] != 0x5c)
        strcat(GameTime + 4, "\\");
    strcat(GameTime + 4, helpFileName);
}