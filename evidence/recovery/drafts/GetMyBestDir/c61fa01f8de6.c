/*
 * GetMyBestDir: entry point for choosing the player ant's move direction.
 * A far counter cell (match_position[0]) selects between three modes:
 * negative on the very first call (falls through to compute an initial
 * direction toward a landmark via GetDir, stash it as MeCrazyDir, arm the
 * counter to 16 and clear MeCrazyRot, then hand off to GetMyRandDirs);
 * zero-or-positive normally (walk GetMyBestDirs up to 64 steps,
 * accumulating the ant's projected position through the Dx8/Dy8
 * direction-delta tables, until it returns a negative direction or the
 * step count reaches 0x40); a walk whose very first GetMyBestDirs call is
 * already the -2 sentinel reruns GetMyRandDirs with the counter left
 * untouched, while any other ending re-picks with a fresh GetMyBestDirs
 * call after resetting the counter to -1, then decrements the counter
 * before returning.
 */
extern int far match_position[];
extern int far MeCrazyDir;
extern int far MeCrazyRot;
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];

extern int far GetDir(int x, int y, int tx, int ty);
extern int far GetMyBestDirs(int a1, int a2, int a3, int a4, int a5);
extern int far GetMyRandDirs(int far *rot, int far *dir, int a1, int a2, int a3, int a4, int a5);

int far GetMyBestDir(int a1, int a2, int a3, int a4, int a5)
{
    int far *pcount;
    int dir;
    int sumx, sumy;
    int idx;

    pcount = &match_position[0];
    if (*pcount < 0) {
        dir = GetMyBestDirs(a1, a2, a3, a4, a5);
        if (dir != -2)
            return dir;

        if (*pcount != dir)
            return dir;

        dir = GetDir(a2, a3, a4, a5) - 1;
        MeCrazyDir = dir;
        *pcount = 0x10;
        MeCrazyRot = 0;
        return GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, a1, a2, a3, a4, a5);
    }

    idx = 0;
    dir = GetMyBestDirs(a1, a2, a3, a4, a5);
    if (dir >= 0) {
        sumx = a2 + (signed char)Dx8[dir];
        sumy = a3 + (signed char)Dy8[dir];
        if (dir >= 0) {
            while (idx < 0x40) {
                dir = GetMyBestDirs(a1, sumx, sumy, a4, a5);
                if (dir >= 0) {
                    sumx += (signed char)Dx8[dir];
                    sumy += (signed char)Dy8[dir];
                }
                idx++;
                if (dir < 0)
                    break;
            }
        }
    }

    if (dir == -2) {
        dir = GetMyRandDirs(&MeCrazyRot, &MeCrazyDir, a1, a2, a3, a4, a5);
    } else {
        *pcount = -1;
        dir = GetMyBestDirs(a1, a2, a3, a4, a5);
    }

    (*pcount)--;
    return dir;
}
