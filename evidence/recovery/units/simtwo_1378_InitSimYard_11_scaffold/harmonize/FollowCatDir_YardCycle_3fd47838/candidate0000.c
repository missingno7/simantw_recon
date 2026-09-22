/* Resolve actual PACK objects through original NE selector slots and exact MAPSYM names; preserve the observed access widths and body behavior. Names do not by themselves prove types or original source. */
extern int far DogPx;
extern int far DogPy;
extern int far YardCycle;
int FollowCatDir(void) {
    int direction;
    direction = DogPx;
    if (direction < 5) return 1;
    if (*(volatile int *)&direction > 8) return 3;
    if (DogPy > 0) return 0;
    return YardCycle & 3;
}
