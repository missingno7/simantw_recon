/* One based record backs both info-window member views. */
typedef struct InfoWindowState {
    unsigned modeAtA434;
    unsigned reservedWords[15];
    unsigned stateAtA454;
    unsigned drawInfoCard;
} InfoWindowState;
static InfoWindowState __based(__segname("SIMANT_DATA_GROUP")) infoWindowState = { 0x80, {0}, 0, 0x80 };
extern void far DisplayCard(unsigned);
extern int far win_IsWinOpen(int window);
extern void far win_Open(int flags);
void win_DrawInfoWindow(unsigned char flags);
void OpenInfoWindow(void);
void far InfoWindowGapPoolStub(void);
#pragma alloc_text(RUN0_TEXT, win_DrawInfoWindow)
#pragma alloc_text(POOLSTUB_TEXT, InfoWindowGapPoolStub)
#pragma alloc_text(RUN1_TEXT, OpenInfoWindow)
void win_DrawInfoWindow(unsigned char flags)
{
    if (flags & 2)
        DisplayCard(infoWindowState.drawInfoCard);
}
void OpenInfoWindow(void)
{
    if (!win_IsWinOpen(0x500)) {
        infoWindowState.drawInfoCard = 0x80;
        infoWindowState.modeAtA434 = 0x80;
        infoWindowState.stateAtA454 = 0;
    }
    win_Open(0x500);
}
void far InfoWindowGapPoolStub(void) { }
