/*
 * processSpider(row, col, mode): handles a spider-tool click/drag at grid
 * cell LifeA[row][col] (simant:6A38). When mode < 1 and the current tool
 * isn't the spider (CurGameTool != 0xb), the pending-target state is
 * simply cleared and the raw click position saved (Starg=-2, StargLife=
 * -1, SMode=0, SuserX=row, SuserY=col, MeCmd=mode) and the function
 * returns. Otherwise the cell's occupant is looked up (LifeA[row][col]);
 * if occupied, FindAntIndex(1, row, col, life) locates the ant record --
 * a hit (>=0) latches it as the new spider target (StargLife=life,
 * Starg=index, SMode=2) and, only while the spider tool is still active,
 * plays the acquire sound (0xf) and hands off to EndTargetMode via
 * MeSMode=6. A miss, or an empty cell, falls through: while the spider
 * tool is active it just plays the miss sound (1) and returns; otherwise
 * it clears the target state exactly as the mode<1 path (Starg=-2,
 * StargLife=-1, SMode=0, SuserX=row, SuserY=col, MeCmd=mode).
 */
extern int far CurGameTool;
extern int far Starg;
extern int far StargLife;
extern int far SMode;
extern int far SuserX;
extern int far SuserY;
extern int far MeCmd;
extern int far MeSMode;
extern unsigned char near LifeA[128][64];

extern int far FindAntIndex(int list, int life, int column, int attribute);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far EndTargetMode(void);

void far processSpider(int row, int col, int mode)
{
    int life;
    int idx;

    if (mode < 1 && CurGameTool != 0xb) {
        Starg = -2;
        StargLife = -1;
        SMode = 0;
        SuserX = row;
        SuserY = col;
        MeCmd = mode;
        return;
    }

    life = LifeA[row][col];
    if (life != 0) {
        idx = FindAntIndex(1, row, col, life);
        if (idx >= 0) {
            StargLife = life;
            Starg = idx;
            SMode = 2;
            if (CurGameTool == 0xb) {
                myBeginSound(0xf, 0, 0x7e);
                MeSMode = 6;
                EndTargetMode();
            }
            return;
        }
    }

    if (CurGameTool == 0xb) {
        myBeginSound(1, 0, 0x7e);
        return;
    }

    Starg = -2;
    StargLife = -1;
    SMode = 0;
    SuserX = row;
    SuserY = col;
    MeCmd = mode;
}
