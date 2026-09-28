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
extern signed char __based(__segname("SIMANT_DATA_GROUP")) ExpSubStates[];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapB[64][64];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapR[64][64];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) Dx8[];
extern int __based(__segname("PACK")) ListIndexB;
extern int __based(__segname("PACK")) ListIndexR;
extern int far TilesDugB;
extern long far TileTotXB;
extern long far TileTotYB;
extern int far TilesDugR;
extern long far TileTotXR;
extern long far TileTotYR;
extern char __based(__segname("SIMANT_DATA_GROUP")) Dx9[];
extern char __based(__segname("SIMANT_DATA_GROUP")) Dy9[];

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
    int mode;
    int idx;
    int result;
    int far * volatile tilesDugB;
    long far * volatile tileTotXB;
    long far * volatile tileTotYB;
    int far * volatile tilesDugR;
    long far * volatile tileTotXR;
    long far * volatile tileTotYR;
    int index;
    register int cx;
    register int cy;

    mode = ExpSubStates[2];
    if (GetAsyncKeyState(0x11) & 0x8000)
        mode ^= 1;

    cx = x;
    cy = y;

    tilesDugB = &TilesDugB;
    tileTotXB = &TileTotXB;
    tileTotYB = &TileTotYB;
    tilesDugR = &TilesDugR;
    tileTotXR = &TileTotXR;
    tileTotYR = &TileTotYR;

    for (;;) {
        if (mode == 0) {
            if (MapPlane == 1 || MapPlane == 0) {
                result = DigMyNewHole(cx, cy);
                if (result != 0) {
                    myBeginSound(1, result, 0x7e);
                    EditMessage(WindPromptStrs[0]->bMsg, 0x78, 0, 1);
                }
            } else if (MapPlane == 2) {
                if (IsItDigable(2, cx, cy)) {
                    if (cy != 0) {
                        DigTileB(cx, cy);
                        if (cy == 1)
                            MakeNewHoleB(cx);
                        myBeginSound(0x13, 0, 0x7e);
                    }
                }
            } else if (MapPlane == 3) {
                if (IsItDigable(3, cx, cy)) {
                    if (cy != 0) {
                        DigTileR(cx, cy);
                        if (cy == 1)
                            MakeNewHoleR(cx);
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
                if (IsItDigable(2, cx, cy)) {
                    if (cy != 0) {
                        idx = (cx << 6) + cy;
                        if (LifeB[idx] != 0) {
                            if (ListIndexB != 0) {
                                index = ListIndexB;
                                while (index) {
                                    --index;
                                    if (Dx8[index + 0x3d18] != 0 &&
                                        Dx8[index + 0x3736] == cx &&
                                        Dx8[index + 0x392c] == cy)
                                        Dx8[index + 0x3d18] = 0;
                                }
                            }
                            LifeB[idx] = 0;
                            MapB[cx][cy] = '.';
                            LifeB[idx] = 0;
                        }

                        if (*tilesDugB > 1) {
                            *tileTotXB -= cx;
                            if (*tileTotXB < 0)
                                *tileTotXB = 0;
                            *tileTotYB -= cy;
                            if (*tileTotYB < 0)
                                *tileTotYB = 0;
                            --*tilesDugB;
                        }

                        SmoothEdgesB(cx, cy - 1);
                        SmoothEdgesB(cx + 1, cy);
                        SmoothEdgesB(cx, cy + 1);
                        SmoothEdgesB(cx - 1, cy);

                        ExitMapB[cx][cy] = 0;
                    }
                }
            } else if (MapPlane == 3) {
                if (IsItDigable(3, cx, cy)) {
                    if (cy != 0) {
                        idx = (cx << 6) + cy;
                        if (LifeR[idx] != 0) {
                            if (ListIndexR != 0) {
                                index = ListIndexR;
                                while (index) {
                                    --index;
                                    if (Dx8[index + 0x46e6] != 0 &&
                                        Dx8[index + 0x4104] == cx &&
                                        Dx8[index + 0x42fa] == cy)
                                        Dx8[index + 0x46e6] = 0;
                                }
                            }
                            LifeR[idx] = 0;
                            MapR[cx][cy] = '.';
                            LifeR[idx] = 0;
                        }

                        if (*tilesDugR > 1) {
                            *tileTotXR -= cx;
                            if (*tileTotXR < 0)
                                *tileTotXR = 0;
                            *tileTotYR -= cy;
                            if (*tileTotYR < 0)
                                *tileTotYR = 0;
                            --*tilesDugR;
                        }

                        SmoothEdgesR(cx, cy - 1);
                        SmoothEdgesR(cx + 1, cy);
                        SmoothEdgesR(cx, cy + 1);
                        SmoothEdgesR(cx - 1, cy);

                        ExitMapR[cx][cy] = 0;
                    }
                }
            }
        }

        result = GetDir(cx, cy, tx, ty);
        idx = result;
        if (Dx9[idx] != 0)
            cx += Dx9[idx];
        else
            cy += Dy9[idx];

        if (idx == 0)
            break;
    }
}
