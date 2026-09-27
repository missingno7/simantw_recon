/*
 * FollowCatDir translates the dog's current x position into the small
 * direction code consumed by the caller: below five gives 1, above eight
 * gives 3; in the middle band a positive DogPy gives 0, else the low two bits
 * of YardCycle.
 *
 * Unit review (simtwo:1378): the isolated candidate had modelled the three far
 * words as invented objects (catDirection[0x3bd8], catModeGate[0x3c4e],
 * catDirectionState[0x7a5c]); the object addresses are the MAPSYM publics
 * DogPx (0x77B0), DogPy (0x789C) and YardCycle (0x7A5C) of segment 9, each
 * through its own selector-pool word, exactly as the admitted unit spells them.
 */
extern int far DogPx;
extern int far DogPy;
extern int far YardCycle;

int FollowCatDir(void)
{
    int direction;

    direction = DogPx;
    if (direction < 5)
        return 1;
    if (*(volatile int *)&direction > 8)
        return 3;
    if (DogPy > 0)
        return 0;
    return YardCycle & 3;
}
