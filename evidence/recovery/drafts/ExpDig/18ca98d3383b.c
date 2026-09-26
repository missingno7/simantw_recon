/*
 * ExpDig: experimental map-editor tool that drags a dig operation from
 * (x, y) toward (tx, ty), one map cell per loop iteration, until GetDir
 * reports arrival (dir == 0).  The behaviour for the whole call is
 * picked once from experiment sub-state 2, XORed with 1 while CONTROL
 * is held: mode 0 starts a new hole (DigMyNewHole, with a placement
 * sound and an edit-message prompt on success, per plane 0/1 vs 2 vs
 * 3); mode 1 performs the actual dig -- for plane 2/3 it is a
 * combined ClearLifeB/R (search and clear the matching far B/R list
 * record when the cell holds life) and FillDirtB/R (clear the cell,
 * shrink the plane's running tile-total/tile-count bookkeeping,
 * smooth the four neighbours and clear the cell's exit-map flag).
 * TilesDugB/R and the tile totals are reached through far pointers set
 * up once before the loop.
 */
extern int near MapPlane;
extern unsigned char far ExpSubStates[];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char far ExitMapB[64][64];
extern unsigned char far ExitMapR[64][64];
extern unsigned char far Dx8[];
extern int far ListIndexB;
extern int far ListIndexR;
extern int far TilesDugB;
extern long far TileTotXB;
extern long far TileTotYB;
extern int far TilesDugR;
extern long far TileTotXR;
extern long far TileTotYR;
extern char far Dx9[];
extern char far Dy9[];

struct WindPrompt {
    char pad[0x54];
    char far *rMsg;
    char far *bMsg;
};
extern struct WindPrompt far * far WindPromptStrs[];

extern int far pascal GetAsyncKeyState(unsigned int key);
extern int far DigMyNewHole(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far EditMessage(char far *text, int x, int y, int flag);
extern int far IsItDigable(int plane, int x, int y);
extern void far DigTileB(int x, int y);
extern void far MakeNewHoleB(int x);
extern void far DigTileR(int x, int y);
extern void far MakeNewHoleR(int x);
extern void far SmoothEdgesB(int x, int y);
extern void far SmoothEdgesR(int x, int y);
extern int far GetDir(int x, int y, int tx, int ty);

void far ExpDig(int x, int y, int tx, int ty)
{
    volatile int mode;
    volatile int idx;
    volatile int result;
    int far *tilesDugB;
    long far *tileTotXB;
    long far *tileTotYB;
    int far *tilesDugR;
    long far *tileTotXR;
    long far *tileTotYR;
    int index;

    mode = ExpSubStates[2];
    if (GetAsyncKeyState(0x11) & 0x8000)
        mode ^= 1;

    tilesDugB = &TilesDugB;
    tileTotXB = &TileTotXB;
    tileTotYB = &TileTotYB;
    tilesDugR = &TilesDugR;
    tileTotXR = &TileTotXR;
    tileTotYR = &TileTotYR;

    for (;;) {
        if (mode == 0) {
            if (MapPlane == 1 || MapPlane == 0) {
                result = DigMyNewHole(x, y);
                if (result != 0) {
                    myBeginSound(1, result, 0x7e);
                    EditMessage(WindPromptStrs[0]->bMsg, 0x78, 0, 1);
                }
            } else if (MapPlane == 2) {
                if (IsItDigable(2, x, y)) {
                    if (y != 0) {
                        DigTileB(x, y);
                        if (y == 1)
                            MakeNewHoleB(x);
                        myBeginSound(0x13, 0, 0x7e);
                    }
                }
            } else if (MapPlane == 3) {
                if (IsItDigable(3, x, y)) {
                    if (y != 0) {
                        DigTileR(x, y);
                        if (y == 1)
                            MakeNewHoleR(x);
                        myBeginSound(1, 0, 0x7e);
                        EditMessage(WindPromptStrs[0]->rMsg, 0xb4, 0, 1);
                    }
                }
            }
        } else {
            if (MapPlane == 1 || MapPlane == 0) {
                myBeginSound(1, 0, 0x7e);
                EditMessage(WindPromptStrs[0]->rMsg, 0xb4, 0, 1);
            } else if (MapPlane == 2) {
                if (IsItDigable(2, x, y)) {
                    if (y != 0) {
                        idx = (x << 6) + y;
                        if (LifeB[idx] != 0) {
                            if (ListIndexB != 0) {
                                index = ListIndexB;
                                while (index) {
                                    --index;
                                    if (Dx8[index + 0x3d18] != 0 &&
                                        Dx8[index + 0x3736] == x &&
                                        Dx8[index + 0x392c] == y)
                                        Dx8[index + 0x3d18] = 0;
                                }
                            }
                            LifeB[idx] = 0;
                            MapB[x][y] = '.';
                            LifeB[idx] = 0;
                        }

                        if (*tilesDugB > 1) {
                            *tileTotXB -= x;
                            if (*tileTotXB < 0)
                                *tileTotXB = 0;
                            *tileTotYB -= y;
                            if (*tileTotYB < 0)
                                *tileTotYB = 0;
                            --*tilesDugB;
                        }

                        SmoothEdgesB(x, y - 1);
                        SmoothEdgesB(x + 1, y);
                        SmoothEdgesB(x, y + 1);
                        SmoothEdgesB(x - 1, y);

                        ExitMapB[x][y] = 0;
                    }
                }
            } else if (MapPlane == 3) {
                if (IsItDigable(3, x, y)) {
                    if (y != 0) {
                        idx = (x << 6) + y;
                        if (LifeR[idx] != 0) {
                            if (ListIndexR != 0) {
                                index = ListIndexR;
                                while (index) {
                                    --index;
                                    if (Dx8[index + 0x46e6] != 0 &&
                                        Dx8[index + 0x4104] == x &&
                                        Dx8[index + 0x42fa] == y)
                                        Dx8[index + 0x46e6] = 0;
                                }
                            }
                            LifeR[idx] = 0;
                            MapR[x][y] = '.';
                            LifeR[idx] = 0;
                        }

                        if (*tilesDugR > 1) {
                            *tileTotXR -= x;
                            if (*tileTotXR < 0)
                                *tileTotXR = 0;
                            *tileTotYR -= y;
                            if (*tileTotYR < 0)
                                *tileTotYR = 0;
                            --*tilesDugR;
                        }

                        SmoothEdgesR(x, y - 1);
                        SmoothEdgesR(x + 1, y);
                        SmoothEdgesR(x, y + 1);
                        SmoothEdgesR(x - 1, y);

                        ExitMapR[x][y] = 0;
                    }
                }
            }
        }

        result = GetDir(x, y, tx, ty);
        idx = result;
        if (Dx9[idx] != 0)
            x += Dx9[idx];
        else
            y += Dy9[idx];

        if (idx == 0)
            break;
    }
}
