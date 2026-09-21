/*
 * StartFightA: an A-list ant at (x, y) attacks the ant occupying (nx, ny).
 * The attacker's type byte (AlistT, SIMANT_DATA_GROUP offset 0x2f62) is
 * saved and cleared together with its LifeA cell; the defender's index
 * comes from the far FindInAList(nx, ny) and, when found, GetWinner (near)
 * decides the outcome from the defender's type and the saved attacker
 * type.  The defender's type becomes the winner's colour bit plus 0x70,
 * its LifeA cell is rewritten the same way, its mode (AlistM, 0x2b78)
 * becomes 0xa and its stamina (AlistS, 0x334c) the winner value, and an
 * alarm of strength 0x28 is raised at the cell (near AlarmHere2).  All
 * three list bytes are reached through one selector slot, so the segment
 * object is a single far byte addressed by offset.
 */
extern unsigned char near LifeA[];
extern int far FindInAList(int x, int y);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);
extern unsigned char far AlistT[];
extern unsigned char far AlistM[];
extern unsigned char far AlistS[];

void near StartFightA(int ant, int x, int y, int nx, int ny)
{
    int loser;
    int type;
    int winner;

    type = AlistT[ant];
    AlistT[ant] = 0;
    LifeA[x * 64 + y] = 0;
    loser = FindInAList(nx, ny);
    if (loser >= 0) {
        winner = GetWinner(AlistT[loser], type);
        AlistT[loser] = (winner & 0x80) + 0x70;
        LifeA[nx * 64 + ny] = (winner & 0x80) + 0x70;
        AlistM[loser] = 0xa;
        AlistS[loser] = winner;
        AlarmHere2(nx, ny, 0x28);
    }
}

