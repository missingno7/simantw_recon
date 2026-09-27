struct HistEvent { char reserved[12]; unsigned int message; };
struct HistLocals { int v2; int v1; int message; };
extern int near win_hwnd[];
extern int far editBufInvalidFlag[];
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far DoWinHelp(int mode);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern int far StillDown(void);
extern void far drawHistGraph(int value, int flag, int index);
extern void far ToggleHistButton(int message);
void far ProcHistoryEvent(struct HistEvent far *event)
{
    struct HistLocals local; unsigned int p; int i;
    local.message=event->message;
    switch(local.message) {
    case 0x150d: DoWinHelp(0x150f); return;
    case 0x150e:
        clip_SetWin(0x1500); MSClipStart(win_hwnd[21]);
        win_FillObjRect(0x150e,ConvColor(0));
        for(i=0,p=0x2f;p<0x33;p++,i++) {
            local.v1=editBufInvalidFlag[p];
            if(local.v1!=(int)0x8000) drawHistGraph(local.v1,1,i);
        }
        while(StillDown()) ;
        win_FillObjRect(0x150e,ConvColor(0));
        for(i=0,p=0x2f;p<0x33;p++,i++) {
            local.v2=editBufInvalidFlag[p];
            if(local.v2!=(int)0x8000) drawHistGraph(local.v2,0,i);
        }
        clip_Off(); MSClipEnd(); return;
    default:
        if(event->message<0x1503) return;
        if(event->message>0x150c) return;
        ToggleHistButton(local.message);
    }
}
