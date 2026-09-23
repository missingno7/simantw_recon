/* Find a valid neighboring nest hole, append its ant record, then compact A-list holes. */
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far match_position[];
extern unsigned char near MapA[];
extern int far IsValidA(int x, int y);

void far ExitHole(int x, int y, int attribute, int mode, int stamina)
{
    unsigned char far *list;
    int direction;
    int newX;
    int newY;
    int count;
    int displacement;
    int source;
    int destination;

    direction = 0;
    while (direction < 8) {
        newX = x + (signed char)Dx8[direction];
        newY = y + (signed char)Dy8[direction];
        if (IsValidA(newX, newY) == 1 &&
            MapA[newX * 64 + newY] == 0x50)
            break;
        ++direction;
    }
    if (direction == 8)
        return 0;

    count = match_position[0x4078];
    list = Dx8;
    list[count + 0x23a4] = (unsigned char)newX;
    list[count + 0x278e] = (unsigned char)newY;
    list[count + 0x2f62] = (unsigned char)attribute;
    list[count + 0x2b78] = (unsigned char)mode;
    if (mode == 6)
        list[count + 0x334c] = (unsigned char)stamina;
    else
        list[count + 0x334c] = 0;

    if (mode != 3 && mode != 7 &&
        (((attribute & 0x80) && x > 0x40) ||
         (!(attribute & 0x80) && x < 0x40)))
        list[count + 0x334c] = 0x78;

    if (count >= 1000)
        return 0;
    match_position[0x4078] = count + 1;

    displacement = 0;
    source = 0;
    while (source < match_position[0x4078]) {
        if (list[source + 0x2f62] != 0) {
            if (displacement != 0) {
                destination = source + displacement;
                list[destination + 0x2f62] = list[source + 0x2f62];
                list[destination + 0x23a4] = list[source + 0x23a4];
                list[destination + 0x278e] = list[source + 0x278e];
                list[destination + 0x2b78] = list[source + 0x2b78];
                list[destination + 0x334c] = list[source + 0x334c];
            }
        } else {
            --displacement;
        }
        ++source;
    }
    match_position[0x4078] += displacement;
    return 1;
}
