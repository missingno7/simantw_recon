/* Candidate reconstruction of the fixed-size water placement loop. */
extern void far PlaceDrop(int value);

void InitWater(void)
{
    int index;
    index = 0;
    do {
        PlaceDrop(0);
        ++index;
    } while (index < 100);
}
