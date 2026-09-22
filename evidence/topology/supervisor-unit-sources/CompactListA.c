/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x4078] -> ListIndexA (one selector word per symbol in the object).
 *
 * Hypothesis: compact the A-side Dx8 records in place.  SI scans the
 * ListIndexA live-record bound and DI is the negative byte/record
 * displacement created by empty records.  A live record is copied backward
 * by that displacement only after a hole has appeared; the five observed
 * fields are the complete record payload.  The final DI adjustment removes
 * the holes from the shared count.
 */
extern int far match_position[];
extern int far ListIndexA;
extern unsigned char far Dx8[];

void far CompactListA(void)
{
    int displacement;
    int source;
    int destination;

    displacement = 0;
    source = 0;
    while (source < ListIndexA) {
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
    ListIndexA += displacement;
}
