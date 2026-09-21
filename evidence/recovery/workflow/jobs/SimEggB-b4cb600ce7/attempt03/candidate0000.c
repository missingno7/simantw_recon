/*
 * SimEggB: advance the B-colony queen's egg-laying cycle.  tindexPtr is
 * an explicit far pointer to the shared cursor Tindex (matching the
 * target's stored 4-byte far-pointer locals, as in DoRestB).  attr
 * starts as the current Dx8[Tindex+0x3d18] (BlistT) type byte and mode
 * starts at -1 (no MakeMe roll yet).  Only on cycle phases where
 * (Cycle & mask)==0 (mask 0x7f once BpopT>2, else 0x1f) does anything
 * change: attr is incremented, and only when (attr&0xf)==8 does an egg
 * actually try to hatch.  Unless ModeAuto is set, a SGRand(255) roll
 * against (an unnamed segment9 word>>7, addressed through
 * match_position[0x4e3c]) can decline the egg (attr reset to 0,
 * TotalEggsDiedB incremented); otherwise MakeMe picks the new mode,
 * attr becomes (mode<<3)+2, and Dx8[Tindex+0x3b22] (BlistM) is set to 1
 * directly (mode==2) or via GetNewModeB(mode) otherwise.  Once
 * BalloonModeFlag is set and no MakeMe roll happened this call
 * (mode<0), EggBalloons(x, y, 2) runs.  The tail always runs
 * regardless of path: LifeB[(x<<6)+y], Dx8[Tindex+0x3d18] (BlistT) and
 * Dx8[Tindex+0x3f0e] (BlistS, cleared) are stamped from the final attr.
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];
extern int near BpopT;
extern int far Cycle;
extern int far ModeAuto;
extern int far match_position[];
extern long far TotalEggsDiedB;
extern int far MakeMe;
extern int far BalloonModeFlag;
extern int far SGRand(int range);
extern int far GetNewModeB(int mode);
extern void far EggBalloons(int x, int y, int plane);

void far SimEggB(int x, int y)
{
    int far *tindexPtr;
    int attr;
    int mode;
    int mask;

    tindexPtr = &Tindex;
    attr = Dx8[*tindexPtr + 0x3d18];
    mode = -1;

    if (BpopT > 2)
        mask = 0x7f;
    else
        mask = 0x1f;
    if (!(Cycle & mask)) {
        attr++;
        if ((attr & 0xf) == 8) {
            if (ModeAuto != 0 || ((unsigned int)match_position[0x4e3c] >> 7) >= (unsigned int)SGRand(255)) {
                mode = MakeMe;
                attr = (mode << 3) + 2;
                if (mode == 2)
                    Dx8[*tindexPtr + 0x3b22] = 1;
                else
                    Dx8[*tindexPtr + 0x3b22] = (unsigned char)GetNewModeB(mode);
            } else {
                attr = 0;
                TotalEggsDiedB++;
            }
        }
    }

    if (BalloonModeFlag != 0 && mode < 0)
        EggBalloons(x, y, 2);

    LifeB[(x << 6) + y] = (unsigned char)attr;
    Dx8[*tindexPtr + 0x3d18] = (unsigned char)attr;
    Dx8[*tindexPtr + 0x3f0e] = 0;
}
