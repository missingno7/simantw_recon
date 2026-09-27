/* Candidate translation unit simone_3120_MakeClip_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _MakeClip */

extern unsigned char near MapA[];
static unsigned char near ClipMask[9] = { 0, '1', '2', '3', '4', '5', '6', '7', 0 };

void MakeClip(int x, int y)
{
    int row;
    int col;
    unsigned char near *mask;

    for (row = 0; row < 3; ++row) {
        col = 0;
        mask = ClipMask + row;
        while (col < 3) {
            if (*mask != 0)
                MapA[(x << 6) + y + col] = *mask;
            mask += 3;
            ++col;
        }
        x++;
    }
}

