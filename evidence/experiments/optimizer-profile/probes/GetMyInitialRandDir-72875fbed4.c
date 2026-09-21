/*
 * Hypothesis: the final five inputs describe the initial position/direction
 * request.  GetDir supplies MeCrazyDir-1, the three persistent direction
 * outputs are initialized, and GetMyRandDirs receives the five inputs plus
 * the observed output references.  The explicit near casts model the
 * target's one-word offsets for match_position and MeCrazyRot; MeCrazyDir
 * remains a far pointer because the target pushes its selector.
 */
extern int far GetDir(int a, int b, int c, int d);
extern void near GetMyRandDirs(int far *rotation,
                               int near *direction,
                               int near *positions,
                               int a, int b, int c, int d, int e);
extern int far match_position[];
extern int far MeCrazyDir;
extern int far MeCrazyCnt;
extern int far MeCrazyRot;

void far GetMyInitialRandDir(int unused1, int unused2, int unused3,
                             int unused4, int count, int a, int b,
                             int c, int d)
{
    int near *positions;

    MeCrazyDir = GetDir(a, b, c, d) - 1;
    MeCrazyCnt = 0x10;
    MeCrazyRot = 0;
    positions = (int near *)match_position;
    GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir, positions,
                  count, a, b, c, d);
}
