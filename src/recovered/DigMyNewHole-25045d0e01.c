/* Return 1 for an open terrain tile or a clear 3x3 location; create the hole on success. */
extern int far TERRAINset;
extern unsigned char near MapA[];
extern int far IsClear3x3(int plane, int x, int y);
extern void far CreateNewHole(int x, int y);

int far DigMyNewHole(int x, int y)
{
    int result;

    result = 0;
    if (x >= 1 && x <= 127 && y >= 1 && y <= 63) {
        if (TERRAINset) {
            if (MapA[(x << 6) + y] < 0xc8)
                result = 1;
        } else {
            result = IsClear3x3(1, x, y);
        }
        if (result == 1)
            CreateNewHole(x, y);
    }
    return result;
}
