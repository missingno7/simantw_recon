/* Build the help path in the PACK scratch bytes immediately after GameTime. */
extern unsigned int near hInst;
extern int far hHelpCursor;
extern unsigned long far GameTime;
extern char far * far helpFileName;
extern unsigned int far pascal LoadCursor(unsigned int instance, char far *name);
extern char far *getcwd(char far *buffer, int maxlen);
extern int strlen(const char far *s);
extern char far *strcat(char far *dest, const char far *src);
void far SetHelpCursor(void)
{
    char far *path;
    path = (char far *)&GameTime + 4;
    hHelpCursor = LoadCursor(hInst, "HelpCursor");
    path = getcwd(path, 0x100);
    {
        int i = 0;
        while (path[i] != 0) ++i;
        if (path[i - 1] != '\\') path[i++] = '\\';
        path[i] = 0;
        i = 0;
        while (helpFileName[i] != 0) { path[strlen(path) + i] = helpFileName[i]; ++i; }
    }
}
