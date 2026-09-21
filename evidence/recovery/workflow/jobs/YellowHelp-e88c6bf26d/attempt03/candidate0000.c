/* Exact PACK:9FE8 symbol MeMode chooses the help topic. Pascal argument evaluation pushes earlier WinHelp arguments before evaluating its conditional final data argument. */
extern int near rootWnd;
extern int near MeType;
extern int far MeMode;
extern char far helpFile[];
extern int far pascal WinHelp(int window,char far *file,unsigned int command,unsigned long data);
void YellowHelp(void)
{
    WinHelp(rootWnd,helpFile,1,
            MeMode == 0 ? (MeType == 0x40 ? 0x00030100L : 0x00010100L) : 0x00020100L);
}
