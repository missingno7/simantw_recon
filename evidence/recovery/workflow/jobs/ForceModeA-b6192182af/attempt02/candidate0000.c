/*
 * ForceModeA: force an A-list ant's state, dispatching on a mode-
 * transition code with a dense switch (cases 1..9, MSC jump table over
 * mode-1). AList fields (Dx8 blob) per src/recovered/wf_GetAntIndex-
 * a8eba5e594.c / wf_SetAntIndex-965b821698.c: life 0x23a4, column
 * 0x278e, attribute 0x2f62, state 0x2b78, direction 0x334c.
 *
 * Case 1 bumps the ant's attribute by 8 before storing the new state and
 * clearing direction. Cases 3/7 drop attribute by 8 and additionally
 * raise the ant's private map cell (MapA, 64-wide band at DGROUP 0x28e8,
 * cell = life*64+column) to at least 0x48 before storing state/direction.
 * Cases 2/6 store state/direction without touching attribute or the map.
 * Cases 5/9 drop attribute by 0x18 before storing state/direction.
 * Cases 4/8 and any other value skip the state/direction store entirely.
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
    int cell;

    switch (mode) {
    case 1:
        AlistT(index) += 8;
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
        AlistT(index) -= 8;
        cell = AlistL(index) * 64 + AlistC(index) + 0x28e8;
        if (MapA[cell] < 0x48)
            MapA[cell] = 0x48;
        AlistM(index) = (unsigned char)value;
        AlistS(index) = 0;
        break;
    case 5:
    case 9:
        AlistT(index) -= 0x18;
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
