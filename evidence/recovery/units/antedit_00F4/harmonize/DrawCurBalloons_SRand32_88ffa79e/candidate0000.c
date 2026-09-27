/* Complete readable draft for DrawCurBalloons. */
struct MapPoint { int x; int y; };

extern int near ELayerMode;
extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int near tileWidth;
extern int near tileHeight;
extern int near editForce;
extern int near scrollBarFlag;
extern int near win_hwnd[];
extern int far editBufInvalidFlag[];
extern int far OptionStates[];
extern int far GamePaused;
extern struct MapPoint far MapPnt;
extern int far FightBalloonCnt;
extern struct MapPoint far LastFightPnt;
extern struct MapPoint far CurFightPnt;
extern int far LastFightPlane;
extern int far CurFightPlane;
extern unsigned long far RFightBalloonTicks;
extern unsigned long far BFightBalloonTicks;
extern int far WantBFightBalloon;
extern int far WantRFightBalloon;
extern int far BFightBalloonIndex;
extern int far RFightBalloonIndex;
extern char far * far * far BFightMsgs;
extern char far * far * far RFightMsgs;
extern int far EggBalloonCnt;
extern struct MapPoint far LastEggPnt;
extern struct MapPoint far CurEggPnt;
extern int far LastEggPlane;
extern int far CurEggPlane;
extern unsigned long far EggBalloonTicks;
extern int far WantEggBalloon;
extern int far EggBalloonIndex;
extern char far * far * far EggMsgs;
extern int far QueenBalloonCnt;
extern struct MapPoint far LastQueenPnt;
extern struct MapPoint far CurQueenPnt;
extern int far LastQueenPlane;
extern int far CurQueenPlane;
extern unsigned long far QueenBalloonTicks;
extern int far WantQueenBalloon;
extern int far QueenBalloonIndex;
extern char far * far * far QueenMsgs;
extern int far RestBalloonCnt;
extern struct MapPoint far LastRestPnt;
extern struct MapPoint far CurRestPnt;
extern int far LastRestPlane;
extern int far CurRestPlane;
extern unsigned long far RestBalloonTicks;
extern int far WantRestBalloon;
extern int far RestBalloonIndex;
extern char far * far * far RestMsgs;
extern int far CurBalloonCnt;
extern struct MapPoint far CurBalloonPnts[];
extern int far CurBalloonPlane[];
extern int far CurBalloonFlags[];
extern char far * far CurBalloonMsgs[];
extern unsigned long far TickCount(void);
extern int far SRand2(void);
extern int far SRand4(void);
extern long far SRand32(void);
extern int far SRand64(void);
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);

void far DrawCurBalloons(void)
{
    int jitter;
    volatile int x;
    volatile int y;
    int plane;
    int visible;
    char far *message;

    /* The draw pass is enabled only for an active edit layer. */
    if (OptionStates[5] == 0)
        return;
    if (ELayerMode != -1)
        return;

    /* A newly observed fight location seeds both fight balloon trackers. */
    if (FightBalloonCnt == 0) {
        if (LastFightPnt.x >= 0 && LastFightPnt.y >= 0) {
            CurFightPnt.x = LastFightPnt.x;
            CurFightPnt.y = LastFightPnt.y;
            CurFightPlane = LastFightPlane;
            FightBalloonCnt++;
            RFightBalloonTicks = 0L;
            BFightBalloonTicks = 0L;
            WantBFightBalloon = 0;
            WantRFightBalloon = 0;
        }
    }

    if (FightBalloonCnt > 0) {
        /* Blue fight message deadline and selection. */
        if (GamePaused == 0) {
            if ((long)TickCount() > (long)BFightBalloonTicks) {
                jitter = SRand32();
                BFightBalloonTicks = (unsigned long)((long)TickCount() + jitter + 0x3cL);
                if (SRand2() == 0) {
                    WantBFightBalloon = 1;
                    BFightBalloonIndex++;
                    if (BFightMsgs[BFightBalloonIndex] == 0)
                        BFightBalloonIndex = 0;
                } else {
                    WantBFightBalloon = 0;
                }
            }
        }
        /* Red fight message deadline and selection. */
        if (GamePaused == 0) {
            if ((long)TickCount() > (long)RFightBalloonTicks) {
                jitter = SRand32();
                RFightBalloonTicks = (unsigned long)((long)TickCount() + jitter + 0x3cL);
                if (SRand2() == 0) {
                    WantRFightBalloon = 1;
                    RFightBalloonIndex++;
                    if (RFightMsgs[RFightBalloonIndex] == 0)
                        RFightBalloonIndex = 0;
                } else {
                    WantRFightBalloon = 0;
                }
            }
        }

        /* Queue the selected blue fight message when its tile is visible. */
        if (WantBFightBalloon != 0) {
            x = CurFightPnt.x;
            y = CurFightPnt.y;
            plane = CurFightPlane;
            message = BFightMsgs[BFightBalloonIndex];
            if (CurBalloonCnt < 6) {
                visible = (MapPlane == plane &&
                           MapPnt.x <= x && x < MapPnt.x + editWidth &&
                           MapPnt.y <= y - 3 && y < MapPnt.y + editHeight);
                if (visible != 0) {
                CurBalloonPnts[CurBalloonCnt].x = tileWidth * x + 8;
                CurBalloonPnts[CurBalloonCnt].y = tileHeight * y + 8;
                CurBalloonPlane[CurBalloonCnt] = plane;
                CurBalloonFlags[CurBalloonCnt] = 0;
                CurBalloonMsgs[CurBalloonCnt] = message;
                CurBalloonCnt++;
                }
            }
        }
        /* Queue the selected red fight message when its tile is visible. */
        if (WantRFightBalloon != 0) {
            x = CurFightPnt.x;
            y = CurFightPnt.y;
            plane = CurFightPlane;
            message = RFightMsgs[RFightBalloonIndex];
            if (CurBalloonCnt < 6) {
                visible = (MapPlane == plane &&
                           MapPnt.x <= x && x < MapPnt.x + editWidth &&
                           MapPnt.y <= y - 3 && y < MapPnt.y + editHeight);
                if (visible != 0) {
                CurBalloonPnts[CurBalloonCnt].x = tileWidth * x + 8;
                CurBalloonPnts[CurBalloonCnt].y = tileHeight * y + 8;
                CurBalloonPlane[CurBalloonCnt] = plane;
                CurBalloonFlags[CurBalloonCnt] = 1;
                CurBalloonMsgs[CurBalloonCnt] = message;
                CurBalloonCnt++;
                }
            }
        }
    }

    /* A newly observed egg location seeds its message tracker. */
    if (EggBalloonCnt == 0) {
        if (LastEggPnt.x >= 0 && LastEggPnt.y >= 0) {
            CurEggPnt.x = LastEggPnt.x;
            CurEggPnt.y = LastEggPnt.y;
            CurEggPlane = LastEggPlane;
            EggBalloonCnt++;
            EggBalloonTicks = 0L;
            WantEggBalloon = 0;
        }
    }

    if (EggBalloonCnt > 0) {
        /* Egg message deadline and selection. */
        if (GamePaused == 0) {
            if ((long)TickCount() > (long)EggBalloonTicks) {
                jitter = SRand32();
                EggBalloonTicks = (unsigned long)((long)TickCount() + jitter + 0xaaL);
                if (SRand4() == 0) {
                    WantEggBalloon = 1;
                    EggBalloonIndex++;
                    if (EggMsgs[EggBalloonIndex] == 0)
                        EggBalloonIndex = 0;
                } else {
                    WantEggBalloon = 0;
                }
            }
        }
        /* Queue the selected egg message when its tile is visible. */
        if (WantEggBalloon != 0) {
            x = CurEggPnt.x;
            y = CurEggPnt.y;
            plane = CurEggPlane;
            message = EggMsgs[EggBalloonIndex];
            if (CurBalloonCnt < 6) {
                visible = (MapPlane == plane &&
                           MapPnt.x <= x && x < MapPnt.x + editWidth &&
                           MapPnt.y <= y - 3 && y < MapPnt.y + editHeight);
                if (visible != 0) {
                CurBalloonPnts[CurBalloonCnt].x = tileWidth * x + 8;
                CurBalloonPnts[CurBalloonCnt].y = tileHeight * y + 8;
                CurBalloonPlane[CurBalloonCnt] = plane;
                CurBalloonFlags[CurBalloonCnt] = 2;
                CurBalloonMsgs[CurBalloonCnt] = message;
                CurBalloonCnt++;
                }
            }
        }
    }

    /* A newly observed queen location seeds its message tracker. */
    if (QueenBalloonCnt == 0) {
        if (LastQueenPnt.x >= 0 && LastQueenPnt.y >= 0) {
            CurQueenPnt.x = LastQueenPnt.x;
            CurQueenPnt.y = LastQueenPnt.y;
            CurQueenPlane = LastQueenPlane;
            QueenBalloonCnt++;
            QueenBalloonTicks = 0L;
            WantQueenBalloon = 0;
        }
    }

    if (QueenBalloonCnt > 0) {
        /* Queen message deadline and selection. */
        if (GamePaused == 0) {
            if ((long)TickCount() > (long)QueenBalloonTicks) {
                jitter = SRand32();
                QueenBalloonTicks = (unsigned long)((long)TickCount() + jitter + 0xb4L);
                if (SRand4() == 0) {
                    WantQueenBalloon = 1;
                    QueenBalloonIndex++;
                    if (QueenMsgs[QueenBalloonIndex] == 0)
                        QueenBalloonIndex = 0;
                } else {
                    WantQueenBalloon = 0;
                }
            }
        }
        /* Queue the selected queen message when its tile is visible. */
        if (WantQueenBalloon != 0) {
            x = CurQueenPnt.x;
            y = CurQueenPnt.y;
            plane = CurQueenPlane;
            message = QueenMsgs[QueenBalloonIndex];
            if (CurBalloonCnt < 6) {
                visible = (MapPlane == plane &&
                           MapPnt.x <= x && x < MapPnt.x + editWidth &&
                           MapPnt.y <= y - 3 && y < MapPnt.y + editHeight);
                if (visible != 0) {
                CurBalloonPnts[CurBalloonCnt].x = tileWidth * x + 8;
                CurBalloonPnts[CurBalloonCnt].y = tileHeight * y + 8;
                CurBalloonPlane[CurBalloonCnt] = plane;
                CurBalloonFlags[CurBalloonCnt] = 2;
                CurBalloonMsgs[CurBalloonCnt] = message;
                CurBalloonCnt++;
                }
            }
        }
    }

    /* A newly observed rest location seeds its message tracker. */
    if (RestBalloonCnt == 0) {
        if (LastRestPnt.x >= 0 && LastRestPnt.y >= 0) {
            CurRestPnt.x = LastRestPnt.x;
            CurRestPnt.y = LastRestPnt.y;
            CurRestPlane = LastRestPlane;
            RestBalloonCnt++;
            RestBalloonTicks = 0L;
            WantRestBalloon = 0;
        }
    }

    if (RestBalloonCnt > 0) {
        /* Rest message deadline and selection. */
        if (GamePaused == 0) {
            if ((long)TickCount() > (long)RestBalloonTicks) {
                jitter = SRand64();
                RestBalloonTicks = (unsigned long)((long)TickCount() + jitter + 0x78L);
                if (SRand2() == 0) {
                    WantRestBalloon = 1;
                    RestBalloonIndex++;
                    if (RestMsgs[RestBalloonIndex] == 0)
                        RestBalloonIndex = 0;
                } else {
                    WantRestBalloon = 0;
                }
            }
        }
        /* Queue the selected rest message when its tile is visible. */
        if (WantRestBalloon != 0) {
            x = CurRestPnt.x;
            y = CurRestPnt.y;
            plane = CurRestPlane;
            message = RestMsgs[RestBalloonIndex];
            if (CurBalloonCnt < 6) {
                visible = (MapPlane == plane &&
                           MapPnt.x <= x && x < MapPnt.x + editWidth &&
                           MapPnt.y <= y - 3 && y < MapPnt.y + editHeight);
                if (visible != 0) {
                CurBalloonPnts[CurBalloonCnt].x = tileWidth * x + 8;
                CurBalloonPnts[CurBalloonCnt].y = tileHeight * y + 8;
                CurBalloonPlane[CurBalloonCnt] = plane;
                CurBalloonFlags[CurBalloonCnt] = 2;
                CurBalloonMsgs[CurBalloonCnt] = message;
                CurBalloonCnt++;
                }
            }
        }
    }

    /* Invalidate the edit window after queuing its first balloon. */
    if (CurBalloonCnt > 0 && editBufInvalidFlag[0] != 0 &&
        scrollBarFlag == 0) {
        editForce = 1;
        InvalidateRect(win_hwnd[0], 0, 0);
    }
}



