/* Rebuild the shared help path in a file-scope far buffer. */
extern unsigned int near hInst;
extern int far hHelpCursor;
extern char far * far helpFileName;
extern unsigned int far pascal LoadCursor(unsigned int instance, char far *name);
extern char far *getcwd(char far *buffer, int maxlen);
extern unsigned int strlen(const char far *s);
extern char far *strcat(char far *dest, const char far *src);
static char far helpPath[256];
void far SetHelpCursor(void)
{
    unsigned int length;
    hHelpCursor = LoadCursor(hInst, "HelpCursor");
    getcwd(helpPath, 0x100);
    length = strlen(helpPath);
    if (length != 0 && helpPath[length - 1] != 0x5c)
        strcat(helpPath, "\\");
    strcat(helpPath, helpFileName);
}