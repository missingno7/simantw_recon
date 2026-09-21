/*
 * ProcEditEvent: dense switch on event->message dispatched through a
 * cs: jump table (18 slots, message 4..21 after "sub ax,4"; holes 5, 19
 * and 20 fall to the shared default). clip_SetWin(0) is called
 * unconditionally before the switch and clip_Off() unconditionally after
 * it (same-segment far calls rewritten by LINK to NOP;PUSH CS;CALL near,
 * targets confirmed against evidence/disassembly/cards.jsonl offsets
 * 36420 "_clip_SetWin" and 36422 "_clip_Off"). Message 15 toggles pause
 * off the far PACK word GamePaused (MAPSYM 0x9c28): "cmp GamePaused,1;
 * sbb ax,ax; neg ax" is the (GamePaused == 0) idiom. Messages 4 and 21
 * share the processEdit(event) body (both jump-table slots point at the
 * same case). The single far-pointer parameter (offset at bp+6, segment
 * at bp+8) matches a lone far struct pointer argument; only the message
 * word at offset 0xc is accessed, so the struct is declared with
 * unresolved padding up to that field.
 */
struct EditEvent {
    char reserved[12];
    int message;
};

extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far processEdit(struct EditEvent far *event);
extern void far DoWinHelp(int mode);
extern void far EditToolsMenu(void);
extern void far SetMapPlane(int plane);
extern void far GotoMyAnt(void);
extern void far GotoSpider(void);
extern void far GotoBQueen(void);
extern void far GotoRQueen(void);
extern int far GamePaused;
extern void far SetPause(int pause);
extern void far EditScentMenu(void);
extern void far DoHealthSetY(int mode, struct EditEvent far *event);
extern void far DoWarnSetB(int mode, struct EditEvent far *event);

void far ProcEditEvent(struct EditEvent far *event)
{
    clip_SetWin(0);

    switch (event->message) {
    case 4:
    case 21:
        processEdit(event);
        break;
    case 6:
        DoWinHelp(2);
        break;
    case 7:
        EditToolsMenu();
        break;
    case 8:
        SetMapPlane(1);
        break;
    case 9:
        SetMapPlane(2);
        break;
    case 10:
        SetMapPlane(3);
        break;
    case 11:
        GotoMyAnt();
        break;
    case 12:
        GotoSpider();
        break;
    case 13:
        GotoBQueen();
        break;
    case 14:
        GotoRQueen();
        break;
    case 15:
        SetPause(GamePaused == 0);
        break;
    case 16:
        EditScentMenu();
        break;
    case 17:
        DoHealthSetY(17, event);
        break;
    case 18:
        DoWarnSetB(18, event);
        break;
    }

    clip_Off();
}
