/* Find a valid neighboring nest hole, add its A-list record, and compact empty records. */
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far match_position[];
extern unsigned char near MapA[];
extern int far IsValidA(int x, int y);
void far ExitHole(int x, int y, int attribute, int mode, int stamina)
{
    register int direction;
    int newX;
    int count;
    int displacement;
    int source;
    int destination;

    direction = 0;
    while (direction < 8) {
        if (IsValidA(x + (signed char)Dx8[direction],
                     y + (signed char)Dy8[direction]) == 1) {
            newX = x + (signed char)Dx8[direction];
            if (MapA[newX * 64 + y + (signed char)Dy8[direction]] < 0x50)
                goto next_direction;
            break;
        }
next_direction:
        ++direction;
    }
    if (direction == 8)
        return 0;
    count = match_position[0x4078];
    Dx8[count + 0x23a4] = (unsigned char)newX;
    Dx8[count + 0x278e] = (unsigned char)(y + (signed char)Dy8[direction]);
    Dx8[count + 0x2f62] = (unsigned char)attribute;
    Dx8[count + 0x2b78] = (unsigned char)mode;
    if (mode == 6)
        Dx8[count + 0x334c] = (unsigned char)stamina;
    else
        Dx8[count + 0x334c] = 0;
    if (mode != 3 && mode != 7 &&
        (((attribute & 0x80) && x > 0x40) ||
         (!(attribute & 0x80) && x < 0x40)))
        Dx8[count + 0x334c] = 0x78;
    if (count >= 1000)
        return 0;
    match_position[0x4078] = count + 1;
    displacement = 0;
    source = 0;
    while (source < match_position[0x4078]) {
        if (Dx8[source + 0x2f62] != 0) {
            if (displacement != 0) {
                destination = displacement + source;
                Dx8[destination + 0x2f62] = Dx8[source + 0x2f62];
                Dx8[destination + 0x23a4] = Dx8[source + 0x23a4];
                Dx8[destination + 0x278e] = Dx8[source + 0x278e];
                Dx8[destination + 0x2b78] = Dx8[source + 0x2b78];
                Dx8[destination + 0x334c] = Dx8[source + 0x334c];
            }
        } else {
            --displacement;
        }
        ++source;
    }
    match_position[0x4078] += displacement;
    return 1;
}
