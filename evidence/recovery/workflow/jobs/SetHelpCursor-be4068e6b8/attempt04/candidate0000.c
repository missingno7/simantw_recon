extern unsigned int near hInst;
extern int far hHelpCursor;
extern char far helpFile[];
extern char far * far helpFileName;

extern unsigned int far pascal LoadCursor(unsigned int instance, char far *name);
extern char far *getcwd(char far *buffer, int maxlen);
extern int _fstrlen(const char far *s);
extern char far *_fstrcat(char far *dest, const char far *src);

void far SetHelpCursor(void)
{
    hHelpCursor = LoadCursor(hInst, "HelpCursor");

    getcwd(helpFile, 0x100);

    if (helpFile[_fstrlen(helpFile) - 1] != '\\')
        _fstrcat(helpFile, "\\");

    _fstrcat(helpFile, helpFileName);
}
