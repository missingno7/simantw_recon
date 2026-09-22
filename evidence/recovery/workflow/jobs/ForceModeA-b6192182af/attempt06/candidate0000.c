/*
 * ForceModeA: force an A-list ant's state, dispatching on a mode-
 * transition code with a dense switch (cases 1..9, MSC jump table over
 * mode-1). AList fields (Dx8 blob) per src/recovered/wf_GetAntIndex-
 * a8eba5e594.c / wf_SetAntIndex-965b821698.c and the same-unit
 * src/recovered/wf_tu_simtwo_0000_Recruit_3-04bd7dd52e.c (Recruit,
 * UnRecruit, RecruitRed): life 0x23a4, column 0x278e, attribute
 * 0x2f62, state 0x2b78, direction 0x334c, all through the array-index
 * extern unsigned char far Dx8[] form used successfully by that unit's
 * other members.
 *
 * Every case adjusts the ant's attribute by a per-case delta (0 for
 * cases 2/6 and 4/8/default; the compiler folds the resulting no-op add
 * away but keeps the far segment load that addresses it). Case 1 uses
 * delta +8, cases 3/7 delta -8 (and additionally clamp the ant's private
 * map cell, MapA at DGROUP 0x28e8, cell = life*64+column, up to at least
 * 0x48 through a near pointer local held on the stack), cases 5/9 delta
 * -0x18. Cases 1, 2/6, 3/7 and 5/9 then store the new state and clear
 * direction; cases 4/8 and any other value skip that store entirely.
 * Finally, whenever the caller asked for state 6 (recruit-to-attack) and
 * the player is on plane 1, the direction byte is overwritten with a
 * code built from the player's near location (MeLocY/MeLocX).
 */
extern unsigned char far Dx8[];
#define AT(off) (Dx8[off])
#define AlistL(i) AT((i) + 0x23a4)
#define AlistC(i) AT((i) + 0x278e)
#define AlistT(i) AT((i) + 0x2f62)
#define AlistM(i) AT((i) + 0x2b78)
#define AlistS(i) AT((i) + 0x334c)

extern unsigned char near MapA[];
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;

void far ForceModeA(int index, int mode, int value)
{
    unsigned char near *p;

    switch (mode) {
    case 1:
        AlistT(index) = AlistT(index) + 8;
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 2:
    case 6:
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 3:
    case 7:
        AlistT(index) = AlistT(index) - 8;
        p = &MapA[AlistL(index) * 64 + AlistC(index) + 0x28e8];
        if (*p < 0x48)
            *p = 0x48;
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 5:
    case 9:
        AlistT(index) = AlistT(index) - 0x18;
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 4:
    case 8:
    default:
        break;
    }

    if (value == 6 && MePlane == 1)
        AlistS(index) = (unsigned char)(((MeLocY & 0xfc) << 2) | (MeLocX >> 3));
}
