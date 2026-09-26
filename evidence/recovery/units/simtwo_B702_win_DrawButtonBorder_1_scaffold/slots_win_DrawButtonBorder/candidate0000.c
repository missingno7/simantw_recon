/* Candidate reconstruction of the button-border diagnostic. */
extern void far WinPrintf(char far *text);

void win_DrawButtonBorder(void)
{
    WinPrintf("JunkRoutine: win_DrawButtonBorder\n");
}
