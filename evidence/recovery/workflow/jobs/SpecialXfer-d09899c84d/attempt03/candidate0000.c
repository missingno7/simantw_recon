/* Transfer the active yard location to the map after a modal pointer event. */
struct YardPoint { int x; int y; };
struct WindPromptTable { unsigned char pad[0x50]; long transferPrompt; };
struct XferEvent { unsigned char pad[2]; int y; int x; unsigned char pad2[4]; };
extern struct YardPoint far CurYardPnt;
extern unsigned char far YMapPopB[12][16];
extern int far ColonyUpdateFlag;
extern int near win_hwnd[];
extern struct WindPromptTable far * far WindPromptStrs;
extern int far patchRgn[];
extern int far mapTileRect[];
extern int far YMapPnt[2];
extern void far MapToYard(void);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinOpen(int window);
extern void far win_ToTop(int window);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far SetYardMode(int mode);
extern void far SetMapPlane(int plane);
extern void far EditMessage(long position, int a, int b, int mode);
extern int far win_GetEvent(struct XferEvent far *event);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far XferPatch(void);

void far SpecialXfer(void)
{
    struct XferEvent event;
    int captured;
    int x;
    int y;

    YMapPopB[CurYardPnt.y][CurYardPnt.x] = 0;
    if (!win_IsWinInFront(0x1900)) {
        if (!win_IsWinOpen(0x1900))
            MapToYard();
        win_ToTop(0x1900);
    }
    captured = MySetCapture(win_hwnd[1]);
    {
        SetYardMode(2);
        ColonyUpdateFlag = 1;
        SetMapPlane(0);
        EditMessage(WindPromptStrs->transferPrompt, -2, -1, 1);
        captured = 0;
        while (win_GetEvent(&event)) {
            if (!win_IsWinInFront(0x1900)) {
                if (win_IsWinOpen(0x1900)) {
                    MapToYard();
                    win_ToTop(0x1900);
                }
            }
            if (captured && win_IsWinInFront(captured))
                break;
        }
        x = (event.x - patchRgn[1] - mapTileRect[1]) / 10;
        y = (event.y - patchRgn[0] - mapTileRect[0]) / 28;
        if (x >= 0 && x <= 15 && y >= 0 && y <= 11 &&
            YMapPopB[y][x] == 0) {
            myBeginSong(0x7e, 0x2afb);
            YMapPnt[0] = y;
            YMapPnt[1] = x;
            XferPatch();
            captured = 1;
        } else {
            myBeginSound(0x78, 0, 1);
            EditMessage(WindPromptStrs->transferPrompt, 0x78, 0, 1);
        }
    }
    if (!captured) {
        MyReleaseCapture();
        EditMessage(0L, -2, -1, 1);
    }
}


