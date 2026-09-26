/* Bounded, readable probe for the observed far path append and prefix copy. */
extern char far Dx8[];
extern char far * far strcat(char far *dest, char far *source);
extern char far * far strcpy(char far *dest, char far *source);

int far pascal OPENDLG(int dialog, int message, int item, int mode, int unused)
{
    char path[0x106];
    char prefix[0x100];
    char far *savedName;
    char far *savedDirectory;

    savedName = (char far *)(Dx8 + 0x9f10);
    savedDirectory = (char far *)(Dx8 + 0x94a0);
    if (message == 0x111 && item == 0x194 && mode == 2) {
        strcat(savedName, path);
        strcpy(savedDirectory, prefix);
    }
    return dialog == unused ? 0 : 0;
}
