/*
 * SetHelpCursor: load the help cursor and build the full help file path.
 * hHelpCursor is loaded via USER LoadCursor("HelpCursor").  helpFile is
 * filled with the current working directory (getcwd), a trailing
 * backslash is appended unless already present, and helpFileName (the
 * relative help file name) is appended to complete the path.
 */
extern unsigned int near hInst;
extern int far hHelpCursor;
extern char far helpFile[];
extern char far * far helpFileName;

extern unsigned int far pascal LoadCursor(unsigned int instance, char far *name);
extern char far *getcwd(char far *buffer, int maxlen);
extern unsigned int far strlen(char far *s);
extern char far *strcat(char far *dest, const char far *src);

void far SetHelpCursor(void)
{
    hHelpCursor = LoadCursor(hInst, "HelpCursor");

    getcwd(helpFile, 0x100);

    if (helpFile[strlen(helpFile) - 1] != '\\')
        strcat(helpFile, "\\");

    strcat(helpFile, helpFileName);
}
