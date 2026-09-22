/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3966] -> ListIndexR (one selector word per symbol in the object).
 *
 * Hypothesis: compact the R-side Dx8 records in place.  SI scans the
 * ListIndexR live-record bound and DI is the negative byte/record
 * displacement created by empty records.  A live record is copied backward
 * by that displacement only after a hole has appeared; the five observed
 * fields are the complete record payload.  The final DI adjustment removes
 * the holes from the shared count.
 */
extern int far match_position[];
extern int far ListIndexR;
extern unsigned char far Dx8[];

void far CompactListR(void)
{
    int displacement;
    int source;
    int destination;

    displacement = 0;
    source = 0;
    while (source < ListIndexR) {
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
    ListIndexR += displacement;
}
