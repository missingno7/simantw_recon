/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x4cea] -> ListIndexB (one selector word per symbol in the object).
 *
 * Hypothesis: compact the B-side Dx8 records in place.  SI scans the
 * ListIndexB live-record bound and DI is the negative byte/record
 * displacement created by empty records.  A live record is copied backward
 * by that displacement only after a hole has appeared; the five observed
 * fields are the complete record payload.  The final DI adjustment removes
 * the holes from the shared count.
 */
extern int far ListIndexB;
extern unsigned char far Dx8[];

void far CompactListB(void)
{
    int displacement;
    int source;
    int destination;

    displacement = 0;
    source = 0;
    while (source < ListIndexB) {
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
    ListIndexB += displacement;
}
