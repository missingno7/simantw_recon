/*
 * GenerateTutorial: build the fixed tutorial world.  CurGameType (far PACK
 * word, selector slot 0xc5bc) is set to 1 while the yard is randomised and
 * 32 black and 32 red ants are added and counted, then to 2 before the
 * player's plane (near MePlane) is applied through SetMapPlane.  Thirty
 * tutorial patches, stored in four private 30-byte signed tables (DGROUP
 * 0x25f0 x, 0x260e y, 0x262c black level, 0x264a red level, fixture
 * bytes below), then seed the black and red yard population grids
 * YMapPopB/YMapPopR (SIMANT_DATA_GROUP, 12 rows of 16, selector slots
 * 0xc61a/0xc61c) with level << 5 at [x][y].  The same-code-group callees
 * are far (LINK nop/push cs/call translation).
 */
extern int far CurGameType;
extern int near MePlane;
extern unsigned char far YMapPopB[12][16];
extern unsigned char far YMapPopR[12][16];
extern void far RandYard(void);
extern void far AddBlackAnts(int count);
extern void far AddRedAnts(int count);
extern void far FullCount(void);
extern void far SetMapPlane(int plane);

static char near tutorialX[30] = {
    0, 1, 2, 5, 7, 2, 2, 7, 8, 6, 3, 7, 7, 10, 11,
    6, 8, 10, 11, 9, 10, 11, 9, 10, 11, 9, 10, 10, 10, 11
};
static char near tutorialY[30] = {
    0, 0, 0, 0, 0, 1, 2, 2, 2, 3, 4, 4, 5, 5, 5,
    6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 10, 11, 11
};
static char near tutorialBlack[30] = {
    2, 4, 6, 5, 7, 4, 2, 2, 3, 6, 1, 7, 4, 5, 3,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0
};
static char near tutorialRed[30] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 6, 3, 4, 6, 5, 6, 3, 0, 4, 3, 2, 5
};

void far GenerateTutorial(void)
{
    int i;

    CurGameType = 1;
    RandYard();
    AddBlackAnts(32);
    AddRedAnts(32);
    FullCount();
    CurGameType = 2;
    SetMapPlane(MePlane);
    for (i = 0; i < 30; i++) {
        YMapPopB[tutorialX[i]][tutorialY[i]] = tutorialBlack[i] << 5;
        YMapPopR[tutorialX[i]][tutorialY[i]] = tutorialRed[i] << 5;
    }
}
