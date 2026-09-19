/* Candidate reconstruction of the quit diagnostic. */
extern void far WinPrintf(char far *text);

void Quit(void)
{
    WinPrintf("JunkRoutine: Quit\n");
}
