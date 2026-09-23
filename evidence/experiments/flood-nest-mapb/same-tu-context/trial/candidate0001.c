/*
 * FloodNestB updates the B-side nest cells in the shared map.  Each row
 * starts at offset three and spans the remaining 0x3d cells.  Values in the
 * flooding band 0x20..0x2d receive the flood increment; low values at or
 * below 0x13 become the full-water marker 0x50.
 */
extern unsigned char near MapB[];

void FloodNestB(void)
{
    int row;
    int cell;
    int value;
    unsigned char near *p;

    for (row = 0; row < 0x1000; row += 0x40) {
        for (cell = 3; cell < 0x40; ++cell) {
            p = MapB + row + cell;
            value = *p;
            if (value >= 0x20 && value <= 0x2d)
                *p += 0x31;
            else if (*p <= 0x13)
                *p = 0x50;
        }
    }
}

/*
 * Hypothesis: compact the A-side Dx8 records in place.  SI scans the
 * match_position[0x4078] live-record bound and DI is the negative byte/record
 * displacement created by empty records.  A live record is copied backward
 * by that displacement only after a hole has appeared; the five observed
 * fields are the complete record payload.  The final DI adjustment removes
 * the holes from the shared count.
 */
extern int far match_position[];
extern unsigned char far Dx8[];

void far CompactListA(void)
{
    int displacement;
    int source;
    int destination;

    displacement = 0;
    source = 0;
    while (source < match_position[0x4078]) {
        if (Dx8[source + 0x2f62] != 0) {
            if (displacement != 0) {
            destination = displacement;
            destination += source;
            Dx8[destination + 0x2f62] =
                Dx8[source + 0x2f62];
            Dx8[destination + 0x23a4] =
                Dx8[source + 0x23a4];
            Dx8[destination + 0x278e] =
                Dx8[source + 0x278e];
            Dx8[destination + 0x2b78] =
                Dx8[source + 0x2b78];
            Dx8[destination + 0x334c] =
                Dx8[source + 0x334c];
            }
        } else {
            --displacement;
        }
        ++source;
    }
    match_position[0x4078] += displacement;
}

/*
 * Hypothesis: compact the B-side Dx8 records in place.  SI scans the
 * match_position[0x4cea] live-record bound and DI is the negative byte/record
 * displacement created by empty records.  A live record is copied backward
 * by that displacement only after a hole has appeared; the five observed
 * fields are the complete record payload.  The final DI adjustment removes
 * the holes from the shared count.
 */
extern int far match_position[];
extern unsigned char far Dx8[];

void far CompactListB(void)
{
    int displacement;
    int source;
    int destination;

    displacement = 0;
    source = 0;
    while (source < match_position[0x4cea]) {
        if (Dx8[source + 0x3d18] != 0) {
            if (displacement != 0) {
                destination = displacement;
                destination += source;
                Dx8[destination + 0x3d18] =
                    Dx8[source + 0x3d18];
                Dx8[destination + 0x3736] =
                    Dx8[source + 0x3736];
                Dx8[destination + 0x392c] =
                    Dx8[source + 0x392c];
                Dx8[destination + 0x3b22] =
                    Dx8[source + 0x3b22];
                Dx8[destination + 0x3f0e] =
                    Dx8[source + 0x3f0e];
            }
        } else {
            --displacement;
        }
        ++source;
    }
    match_position[0x4cea] += displacement;
}

/*
 * Hypothesis: compact the R-side Dx8 records in place.  SI scans the
 * match_position[0x3966] live-record bound and DI is the negative byte/record
 * displacement created by empty records.  A live record is copied backward
 * by that displacement only after a hole has appeared; the five observed
 * fields are the complete record payload.  The final DI adjustment removes
 * the holes from the shared count.
 */
extern int far match_position[];
extern unsigned char far Dx8[];

void far CompactListR(void)
{
    int displacement;
    int source;
    int destination;

    displacement = 0;
    source = 0;
    while (source < match_position[0x3966]) {
        if (Dx8[source + 0x46e6] != 0) {
            if (displacement != 0) {
                destination = displacement;
                destination += source;
                Dx8[destination + 0x46e6] =
                    Dx8[source + 0x46e6];
                Dx8[destination + 0x4104] =
                    Dx8[source + 0x4104];
                Dx8[destination + 0x42fa] =
                    Dx8[source + 0x42fa];
                Dx8[destination + 0x44f0] =
                    Dx8[source + 0x44f0];
                Dx8[destination + 0x48dc] =
                    Dx8[source + 0x48dc];
            }
        } else {
            --displacement;
        }
        ++source;
    }
    match_position[0x3966] += displacement;
}

