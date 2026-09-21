/*
 * Recruit: turn up to count idle ants into recruits.  The A list and
 * then the B list are walked from the top index downwards while count
 * remains positive; an ant whose type byte is nonzero, not red (bit 7
 * clear) and of caste 2 or 6 (bits 3-6) and whose mode is not already 6
 * gets mode 6 with state 0, consuming one recruit.  The list bytes are
 * addressed through the Dx8 far object (AlistT 0x2f62, AlistM 0x2b78,
 * AlistS 0x334c, BlistT 0x3d18, BlistM 0x3b22, BlistS 0x3f0e); the
 * compiler keeps that segment in DS for each loop.
 */
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define AlistT(i) AT((i) + 0x2f62)
#define AlistM(i) AT((i) + 0x2b78)
#define AlistS(i) AT((i) + 0x334c)
#define BlistT(i) AT((i) + 0x3d18)
#define BlistM(i) AT((i) + 0x3b22)
#define BlistS(i) AT((i) + 0x3f0e)
extern int far ListIndexA;
extern int far ListIndexB;

void far Recruit(int count)
{
    int i;
    int n;
    int type;
    int caste;

    n = count;
    for (i = ListIndexA; i > 0 && n > 0; ) {
        i--;
        type = AlistT(i);
        if (type != 0 && !(type & 0x80)) {
            caste = (type & 0x78) >> 3;
            if (caste == 2 || caste == 6) {
                if (AlistM(i) != 6) {
                    AlistM(i) = 6;
                    AlistS(i) = 0;
                    n--;
                }
            }
        }
    }
    for (i = ListIndexB; i > 0 && n > 0; ) {
        i--;
        type = BlistT(i);
        if (type != 0 && !(type & 0x80)) {
            caste = (type & 0x78) >> 3;
            if (caste == 2 || caste == 6) {
                if (BlistM(i) != 6) {
                    BlistM(i) = 6;
                    BlistS(i) = 0;
                    n--;
                }
            }
        }
    }
}

