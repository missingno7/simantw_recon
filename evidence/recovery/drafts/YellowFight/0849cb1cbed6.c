/*
 * YellowFight: resolve a fight between the player ant and the Dx8 record
 * `idx` on the given plane.  Three (life,col,attr) field triples live at
 * fixed offsets into the shared Dx8 blob, selected by plane (<=1, ==2, or
 * otherwise) the same way DoAntSimB/DoAntSimR select their own B/R
 * triples.  ClearLife erases the opponent's old cell, then GetWinner
 * compares MeType against the opponent's attribute byte.  On a loss for
 * the opponent (winner==MeType) the player is stamped back down with
 * SetMyLife, a queen-plane opponent is reported to DeadAntHere with its
 * high attribute bit, its attribute cell is cleared, and a matching
 * MeCmd/MeTargLifePlane/MeTargIndex triple triggers ResetYellowVars.
 * Otherwise the player loses: GotoMyAnt/AnimYellowFight animate the
 * fight, the opponent's cell is restored with SetLife, a queen-plane
 * opponent is reported to DeadAntHere against the player's own position,
 * and YellowDeath(0) ends the player.
 */
extern unsigned char far Dx8[];

extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern int near MeColor;
extern int far MeCmd;
extern int far MeTargLifePlane;
extern int far MeTargIndex;

extern void far ClearLife(int plane, int x, int y, int code);
extern void far SetLife(int plane, int x, int y, int code);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern int near GetWinner(int defender, int attacker);
extern void far GotoMyAnt(void);
extern int far AnimYellowFight(int plane, int x, int y, int dir, int a, int b);
extern int far DeadAntHere(int x, int y, int color);
extern void far ResetYellowVars(int plane, int x, int y);
extern void far YellowDeath(int code);

void far YellowFight(int plane, int idx)
{
    unsigned char far *lifePtr;
    unsigned char far *colPtr;
    unsigned char far *attrPtr;
    int life, col, attr;
    int winner;

    if (plane <= 1) {
        lifePtr = &Dx8[0x23a4];
        colPtr = &Dx8[0x278e];
        attrPtr = &Dx8[0x2f62];
    } else if (plane == 2) {
        lifePtr = &Dx8[0x3736];
        colPtr = &Dx8[0x392c];
        attrPtr = &Dx8[0x3d18];
    } else {
        lifePtr = &Dx8[0x4104];
        colPtr = &Dx8[0x42fa];
        attrPtr = &Dx8[0x46e6];
    }

    attr = attrPtr[idx];
    col = colPtr[idx];
    lifePtr += idx;
    life = *lifePtr;

    ClearLife(plane, life, col, attr);

    attr = attrPtr[idx];
    winner = GetWinner(MeType, attr);

    if (winner != MeType) {
        GotoMyAnt();
        AnimYellowFight(MePlane, MeLocX, MeLocY, MeDir, 0x70, 0);
    }

    if (winner == MeType) {
        SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);

        if (plane <= 1) {
            attr = attrPtr[idx];
            col = colPtr[idx];
            life = *lifePtr;
            DeadAntHere(life, col, attr & 0x80);
        }

        attrPtr[idx] = 0;

        if (MeCmd == 3 && MeTargLifePlane == MePlane && MeTargIndex == idx)
            ResetYellowVars(MePlane, MeLocX, MeLocY);
        return;
    }

    attr = attrPtr[idx];
    col = colPtr[idx];
    life = *lifePtr;
    SetLife(plane, life, col, attr);

    if (plane <= 1)
        DeadAntHere(MeLocX, MeLocY, MeColor);

    YellowDeath(0);
}
