/* Candidate translation unit simant1_96D4_GetNewRedTask_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GetNewRedTask, _GetRedBestDirs
 * SCAFFOLDED: unclaimed members _DoRedInitiator are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near MePlane;
extern int near MeLocX;
extern int far RedTask;
extern int far LastFoodDrop[2];
extern int far RedDestX;
extern int far RedDestY;
extern int far ModePopB[];
extern int near CastePopR[];
extern void far UnRecruitRed(void);
extern int far SRand1(int range);
extern void far RecruitRed(int count);
extern char far Dx8[];
extern char far Dy8[];
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far TileCanBeMovedOn(int plane, int nx, int ny, int plane2, int a, int b, int flag);
extern int far GetLife(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);

extern int far AlistX;  /* scaffold reference for pool word C632 (segment 8, MAPSYM_SITE_NAME) */
extern int far RedLocX;  /* scaffold reference for pool word C634 (segment 9, MAPSYM_SITE_NAME) */
extern int far RedLocY;  /* scaffold reference for pool word C636 (segment 9, MAPSYM_SITE_NAME) */
extern int far RedPlane;  /* scaffold reference for pool word C638 (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C63E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word C640 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C642 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C644 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C646 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoRedInitiator(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoRedInitiator)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoRedInitiator.
 * It only reproduces the object's selector-pool allocation order for the
 * words C632 C634 C636 C638 C63A C63C C63E C640 C642 C644 C646 C648 C64A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoRedInitiator(void)
{
    volatile int t;

    t = AlistX;
    t = RedLocX;
    t = RedLocY;
    t = RedPlane;
    t = (int)RedTask;
    t = ModePopB[0];
    t = Dx9;
    t = match_position;
    t = match_length;
    t = pack_buf;
    t = Scycle;
    t = Dy8[0];
    t = Dx8[0];
}

void far GetNewRedTask(void)
{
    UnRecruitRed();

    if (MePlane == 1) {
        if (SRand1(32) + 0x40 < MeLocX) {
            if (SRand1(10) < ModePopB[5]) {
                RedTask = 2;
                RecruitRed(ModePopB[5]);
                return;
            }
        }
    }

    RedDestY = LastFoodDrop[1];
    RedDestX = LastFoodDrop[0];
    if (RedDestX > 0x1e) {
        RedDestX -= 5;
    } else {
        if (RedDestY < 0x14)
            RedDestY += 5;
        else if (RedDestY > 0x28)
            RedDestY -= 5;
    }

    {
        int redPopulation;
        redPopulation = CastePopR[1] + CastePopR[2];
        if (redPopulation < 0x14)
            RecruitRed(redPopulation >> 2);
        else
            RecruitRed(redPopulation >> 3);
    }
    RedTask = 1;
}

int far GetRedBestDirs(int plane, int x, int y, int a, int b)
{
    int best;
    int fallback;
    int threshold;
    int dir;
    int nx;
    int ny;
    int dis;

    best = -1;
    threshold = GetDis(x, y, a, b);
    if (threshold <= 0)
        goto done;

    fallback = -2;
    for (dir = 0; dir < 8; dir++) {
        ny = Dy8[dir] + y;
        nx = Dx8[dir] + x;
        if (TileCanBeMovedOn(plane, nx, ny, plane, a, b, 0) == 1) {
            dis = GetDis(nx, ny, a, b);
            if (dis < threshold) {
                if (GetLife(plane, nx, ny) > 0 || IsClearTile(plane, nx, ny) != 1)
                    fallback = dir;
                else
                    best = dir;
                threshold = dis;
            }
        }
    }
    if (best < 0)
        best = fallback;
done:
    return best;
}

