/* Candidate translation unit simone_16AE_DigMyNewHole_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DigMyNewHole, _CanBeHouseHole
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern int far TERRAINset;
extern unsigned char near MapA[];
extern int far IsClear3x3(int plane, int x, int y);
extern void far CreateNewHole(int x, int y);


int CanBeHouseHole(int direction);

#pragma alloc_text(RUN2_TEXT, CanBeHouseHole)

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

int CanBeHouseHole(int direction)
{
    if (direction == 0)
        return 0x86;

    if (direction == 2)
        return 0x8a;
    if (direction == 3)
        return 0x8a;

    if (direction >= 0x5e) {
        if (direction < 0x62)
            return direction + 0x22;
        if (direction == 0x66)
            return 0x85;
        if (direction == 0x68)
            return 0x84;
    }

    return 0;
}

