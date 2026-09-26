/*
 * XferPatch: move the active yard patch to the pending map point
 * (YMapPnt), validating first.  No-op if the pending point already
 * equals the current one (CurYardPnt).  Outside the colony game type
 * (CurGameType != 2) the transfer is always refused (dialog 0x2710).
 * In the colony game, a transfer is also refused while both colonies
 * are still small (ColonyTotalBlack <= 1 && BpopT <= 1, dialog 0x2712).
 * Otherwise, if the destination tile's black population
 * (YMapPopB[x][y], row stride 16) is empty, the transfer is refused
 * unless the player is already placing a black nest there
 * (MeType == 0x40 && MeNestStarted == 0; else dialog 0x2714).  On
 * success: a jingle plays, CurYardPnt is updated, the map redraws,
 * JustXfered/queen and swarm counters reset, the queen-storage display
 * is invalidated, MeNestStarted is set, and RandWorld reseeds the new
 * patch from its saved seed/population.  If the new tile's red
 * population is empty, HealthR resets.  A trailing helper call runs
 * (no recovered name), then a final success dialog is shown, with the
 * message depending on whether the tile index is within the first 37
 * cells (0x24).
 */
struct MapPoint { int x, y; };

extern struct MapPoint far YMapPnt;
extern struct MapPoint far CurYardPnt;
extern int far CurGameType;
extern int near ColonyTotalBlack;
extern int near BpopT;
extern unsigned char far YMapPopB[];
extern int near MeType;
extern int far MeNestStarted;
extern unsigned char far YMapPopR[];
extern int far YMapSeeds[];
extern int near QueenStorageB;
extern int near QueenStorageR;
extern int far JustXfered;
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int near HealthR;

extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void near PictStrnDialog(int a, int messageId, int flag);
extern void far DrawMap(void);
extern void near InvalQueenStorageDisp(void);
extern void far RandWorld(int seed, int blackSize, int redSize, int mapWidth, int mapKind);
extern void near ClearBookmarks(void);  /* MAPSYM binds this wrapped same-segment call to ClearBookmarks. */

void far XferPatch(void)
{
    int x, y;
    int idx;

    y = YMapPnt.y;
    x = YMapPnt.x;

    if (x == CurYardPnt.x && y == CurYardPnt.y)
        return;

    if (CurGameType != 2) {
        myBeginSound(1, 0, 0x7e);
        PictStrnDialog(0, 0x2710, 1);
        return;
    }
    if (ColonyTotalBlack <= 1 && BpopT <= 1) {
        myBeginSound(1, 0, 0x7e);
        PictStrnDialog(0, 0x2712, 1);
        return;
    }

    idx = (x << 4) + y;
    if (YMapPopB[idx] < 1) {
        if (MeType != 0x40 || MeNestStarted != 0) {
            myBeginSound(1, 0, 0x7e);
            PictStrnDialog(0, 0x2714, 1);
            return;
        }
    }

    myBeginSong(0x2afa, 0x7e);
    CurYardPnt.x = x;
    CurYardPnt.y = y;
    DrawMap();
    JustXfered = 1;
    QueenStorageB = 0;
    QueenStorageR = 0;
    SwarmCntB = 0;
    SwarmCntR = 0;
    InvalQueenStorageDisp();
    MeNestStarted = 1;

    RandWorld(YMapSeeds[y * 12 + x], YMapPopB[idx], YMapPopR[idx], x, y);

    if (YMapPopR[idx] == 0)
        HealthR = 0;
    ClearBookmarks();

    if (idx > 0x24)
        PictStrnDialog(0, 0x2716, 0);
    else
        PictStrnDialog(0, 0x2717, 0);
}
