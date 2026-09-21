/*
 * PickupMyEgg: the player's ant tries to pick up an egg at (plane, x, y).
 * Only an ant of type 0x10 (a queen) or one whose health is below 10
 * may do so.  The carried-egg slot is first marked 0xfd; FindEggAt
 * returns the egg's list number (negative if none) and its index through
 * a near pointer.  The egg's list entry is cleared with SetAntIndex, and
 * unless the egg lies on the player's own cell its life cell is cleared.
 * A healthy ant then plays sound 0x1c, records the carried egg and
 * becomes type 8; a starving ant instead eats it (food type 3).
 */
extern int near MeType;
extern int near MeHealth;
extern int near MeLocX;
extern int near MeLocY;
extern int far MeEggCarried;
extern int far MeFoodInType;

extern int near FindEggAt(int far *index, int plane, int x, int y);
extern void near SetAntIndex(int plane, int index, int a, int b, int c, int d, int e);
extern void near SetLife(int plane, int x, int y, int value);
extern void far myBeginSound(int sound, int a, int b);

int far PickupMyEgg(int plane, int x, int y)
{
    int index;
    int egg;

    if (MeType != 0x10 && MeHealth >= 10)
        return 0;
    MeEggCarried = 0xfd;
    egg = FindEggAt(&index, plane, x, y);
    if (egg < 0)
        return 0;
    SetAntIndex(plane, index, 0, 0, 0, 0, 0);
    if (x != MeLocX || y != MeLocY)
        SetLife(plane, x, y, 0);
    if (MeHealth < 10)
        MeFoodInType = 3;
    else {
        myBeginSound(0x1c, 0, 0x7e);
        MeEggCarried = egg;
        MeType = 8;
    }
    return 1;
}
