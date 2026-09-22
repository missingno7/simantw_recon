/*
 * ForceModeB: force a B-list ant's state, dispatching on a mode-
 * transition code with a dense switch (cases 1..9, MSC jump table over
 * mode-1); the B-list twin of ForceModeA/RecruitRed with no map-clamp
 * step. BList fields (Dx8 blob) per src/recovered/wf_GetAntIndex-
 * a8eba5e594.c / wf_SetAntIndex-965b821698.c and the same-unit
 * src/recovered/wf_tu_simtwo_0000_Recruit_3-04bd7dd52e.c (Recruit,
 * UnRecruit, RecruitRed): attribute 0x3d18, state 0x3b22, direction
 * 0x3f0e, through the array-index extern unsigned char far Dx8[] form
 * used successfully by that unit's other members.
 *
 * Every case adjusts the ant's attribute by a per-case delta (0 for
 * cases 2/6 and 4/8/default; the compiler folds the resulting no-op add
 * away but keeps the far segment load that addresses it). Case 1 uses
 * delta +8, cases 3/7 delta -8, cases 5/9 delta -0x18. Cases 1, 2/6,
 * 3/7 and 5/9 then store the new state and clear direction; cases 4/8
 * and any other value skip that store entirely. Finally, whenever the
 * caller asked for state 6 (recruit-to-attack) and the player is on
 * plane 1, the direction byte is overwritten with a code built from the
 * player's near location (MeLocY/MeLocX).
 */
extern unsigned char far Dx8[];
#define AT(off) (Dx8[off])
#define BlistT(i) AT((i) + 0x3d18)
#define BlistM(i) AT((i) + 0x3b22)
#define BlistS(i) AT((i) + 0x3f0e)

extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;

void far ForceModeB(int index, int mode, int value)
{
    switch (mode) {
    case 1:
        BlistT(index) += 8;
        BlistM(index) = (unsigned char)value;
        BlistS(index) = 0;
        break;
    case 2:
    case 6:
        BlistM(index) = (unsigned char)value;
        BlistS(index) = 0;
        break;
    case 3:
    case 7:
        BlistT(index) -= 8;
        BlistM(index) = (unsigned char)value;
        BlistS(index) = 0;
        break;
    case 5:
    case 9:
        BlistT(index) -= 0x18;
        BlistM(index) = (unsigned char)value;
        BlistS(index) = 0;
        break;
    case 4:
    case 8:
    default:
        break;
    }

    if (value == 6 && MePlane == 1)
        BlistS(index) = (unsigned char)(((MeLocY & 0xfc) << 2) | (MeLocX >> 3));
}
