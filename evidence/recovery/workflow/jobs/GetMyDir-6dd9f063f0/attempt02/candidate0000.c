/*
 * GetMyDir: pick a heading from (p2,p3) considering a target selected by
 * p1/p4.  When p4<=1 (p1<=1 side) or p4==p1 (p1>1 side) the target is
 * simply (p5,p6); otherwise it is one of the four fixed yard landmarks
 * (LastNewHoleB/R for the p1<=1 side keyed by p4==2, LastNewExitB/R for
 * the p1>1 side keyed by p1==2).  A shared match_position[0] counter
 * (same idiom as GetMyBestDir) selects between two shapes per target
 * family: while armed (>=0) a CheckMyBestDirs probe decides between a
 * fresh GetMyBestDirs commit (decrementing the counter) and a
 * GetMyRandDirs fallback that reuses MeCrazyDir/MeCrazyRot; once
 * disarmed (<0) GetMyBestDirs is tried directly, and only a fresh -2 that
 * still matches the counter re-seeds MeCrazyDir/MeCrazyRot via GetDir
 * before falling back to GetMyRandDirs.  The (p5,p6) family always
 * decrements the counter on every return; the landmark family only
 * decrements when the counter was still armed.
 */
extern int far match_position[];
extern int far LastNewExitB[2];
extern int far LastNewHoleB[2];
extern int far LastNewExitR[2];
extern int far LastNewHoleR[2];
extern int far MeCrazyDir;
extern int far MeCrazyRot;

extern int far GetMyBestDirs(int a1, int a2, int a3, int a4, int a5);
extern int far GetMyRandDirs(int far *rot, int far *dir, int a1, int a2, int a3, int a4, int a5);
extern int far GetDir(int x, int y, int tx, int ty);
extern int far CheckMyBestDirs(int a1, int a2, int a3, int a4, int a5, int far *out);

int far GetMyDir(int p1, int p2, int p3, int p4, int p5, int p6)
{
    int far *pcount;
    int dir;
    int chk;
    int tmp;
    int tx, ty;

    if (p1 <= 1) {
        if (p4 <= 1)
            goto family1;

        if (p4 == 2) {
            tx = LastNewHoleB[0];
            ty = LastNewHoleB[1];
        } else {
            tx = LastNewHoleR[0];
            ty = LastNewHoleR[1];
        }
        goto family2;
    }

    if (p4 == p1)
        goto family1;

    if (p1 == 2) {
        tx = LastNewExitB[0];
        ty = LastNewExitB[1];
    } else {
        tx = LastNewExitR[0];
        ty = LastNewExitR[1];
    }

family2:
    pcount = &match_position[0];
    if (*pcount >= 0) {
        chk = CheckMyBestDirs(p1, p2, p3, tx, ty, &tmp);
        if (chk == -2) {
            dir = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, p1, p2, p3, tx, ty);
        } else {
            *pcount = -1;
            dir = GetMyBestDirs(p1, p2, p3, tx, ty);
        }
        (*pcount)--;
        return dir;
    }

    dir = GetMyBestDirs(p1, p2, p3, tx, ty);
    if (dir != -2)
        return dir;
    if (*pcount == dir) {
        dir = GetDir(p2, p3, tx, ty) - 1;
        MeCrazyDir = dir;
        *pcount = 0x10;
        MeCrazyRot = 0;
        dir = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, p1, p2, p3, tx, ty);
    }
    return dir;

family1:
    pcount = &match_position[0];
    if (*pcount >= 0) {
        chk = CheckMyBestDirs(p1, p2, p3, p5, p6, &tmp);
        if (chk != -2) {
            *pcount = -1;
            dir = GetMyBestDirs(p1, p2, p3, p5, p6);
            (*pcount)--;
            return dir;
        }
        dir = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, p1, p2, p3, p5, p6);
        (*pcount)--;
        return dir;
    }

    dir = GetMyBestDirs(p1, p2, p3, p5, p6);
    if (dir != -2)
        return dir;
    if (*pcount == dir) {
        dir = GetDir(p2, p3, p5, p6) - 1;
        MeCrazyDir = dir;
        *pcount = 0x10;
        MeCrazyRot = 0;
        dir = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, p1, p2, p3, p5, p6);
    }
    return dir;
}
