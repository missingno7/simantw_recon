/*
 * DoRedInitiator: remember this ant's position as the red initiator.  A zero
 * match_position state can either promote a batch of ants to recruiting mode
 * or initialize the red destination from LastFoodDrop and recruit by the
 * configured factor.  State 2 follows the red destination with GetRedBestDirs;
 * an occupied destination can trigger YellowFight or turn an existing red ant.
 * The adjacent LastFoodDrop words and unnamed threshold/coordinate fields are
 * inferred from segment and offset evidence in the inspection packet.
 */
extern unsigned char far AlistX[];
extern unsigned char far AlistY[];
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far MePlane;
extern int near MeLocX;
extern int far RedLocX;
extern int far RedLocY;
extern int far RedPlane;
extern int far RedDestX;
extern int far RedDestY;
extern int far FuzLocX;
extern int far FuzLocY;
extern int far RedTask;
extern int far ModePopB[];
extern int far match_position[];
extern int far LastFoodDrop[2];
extern int near redFactorA;
extern int near redFactorB;

extern void far UnRecruitRed(void);
extern int far SRand1(int range);
extern void far RecruitRed(int count);
extern int near GetRedBestDirs(int plane, int x, int y, int a, int b);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int near RandTurn(int turn);

void far DoRedInitiator(int ant)
{
    int x;
    int y;
    int type;
    int attr;
    int mode;
    int dir;
    int nextX;
    int nextY;
    int occupant;

    y = AlistY[ant];
    type = Dx8[ant + 0x2f62];
    attr = type & 0xf8;
    x = AlistX[ant];
    RedLocX = x;
    RedLocY = y;
    RedPlane = 1;

    if (match_position[0] == 2)
        goto follow_destination;
    if (match_position[0] != 0)
        return;

    UnRecruitRed();
    if (MePlane == 1) {
        if (SRand1(0x20) + 0x40 < MeLocX) {
            if (SRand1(10) < ModePopB[5]) {
                match_position[0] = 2;
                RecruitRed(ModePopB[5]);
                return;
            }
        }
    }

    RedDestY = LastFoodDrop[1];
    RedDestX = LastFoodDrop[0];
    if (RedDestX <= 0x1e) {
        if (RedDestY > 0x1e)
            RedDestX -= 5;
        else if (RedDestY < 0x14)
            RedDestX += 5;
    } else {
        RedDestX -= 5;
    }
    mode = redFactorA + redFactorB;
    if (mode < 0x14)
        RecruitRed(mode >> 2);
    else
        RecruitRed(mode >> 3);
    RedTask = 1;
    return;

follow_destination:
    if (MePlane != 1)
        return;

    RedDestX = FuzLocX;
    RedDestY = FuzLocY;
    dir = GetRedBestDirs(1, RedLocX, RedLocY, RedDestX, RedDestY);
    if (dir < 0) {
        if (SRand1(10) == 0) {
            match_position[0] = 0;
            goto try_step;
        }
        return;
    }

try_step:
    nextY = y + Dy8[dir];
    nextX = x + Dx8[dir];
    occupant = Dx8[(nextX << 6) + nextY + 0x68e8];
    if (occupant != 0) {
        if (IsYellowAnt(occupant) == 1) {
            YellowFight(1, ant);
            return;
        }
        if (occupant <= 0x7f)
            return;
        mode = RandTurn(type & 7) | attr;
        Dx8[(nextX << 6) + nextY + 0x68e8] = (unsigned char)mode;
        Dx8[ant + 0x2f62] = (unsigned char)mode;
        AlistX[ant] = (unsigned char)nextX;
        AlistY[ant] = (unsigned char)nextY;
    } else {
        mode = attr | dir;
        Dx8[(nextX << 6) + nextY + 0x68e8] = (unsigned char)mode;
        Dx8[ant + 0x2f62] = (unsigned char)mode;
        AlistX[ant] = (unsigned char)nextX;
        AlistY[ant] = (unsigned char)nextY;
    }
}
