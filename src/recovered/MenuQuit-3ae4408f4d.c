/* Menu quit prompt and its per-object latch. */
extern int near rootWnd;
static int quitFlag=0;
extern int far pascal MessageBox(int window, char far *text, char far *caption, unsigned style);
extern int far SaveGame(int mode);
int MenuQuit(void) {
    if(quitFlag==0) { switch(MessageBox(rootWnd,"Do you want to save the current ant hill?","SimAnt Quit",0x1123)) {
    case 6: if(SaveGame(0)!=0) { quitFlag=1; return 1; } return 0;
    case 2: return 0; default: quitFlag=1; return 1; } } return 1;
}
