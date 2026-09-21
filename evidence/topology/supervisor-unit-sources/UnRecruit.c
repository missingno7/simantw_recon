/*
 * UnRecruit: give back up to n recruited ants across the A, B and R lists,
 * where n is derived from an unnamed private PACK-segment counter (no
 * MAPSYM public name; lies in the unnamed gap between _TemBModePop and
 * _LoadStr in PACK) -- either half of it (all == 0) or the counter plus 100
 * (all != 0, effectively "un-recruit everything currently recruitable").
 * Each list is walked from the top index downwards while n remains
 * positive; a non-red, nonzero-type ant currently in mode 6 (recruited)
 * has its mode reset (0 for A/B, 7 for R) and consumes one of n.  The list
 * bytes are addressed through the Dx8 far object, matching the admitted
 * Recruit (AlistT 0x2f62, AlistM 0x2b78, BlistT 0x3d18, BlistM 0x3b22) plus
 * a third R list (RlistT 0x46e6, RlistM 0x44f0); the compiler keeps that
 * segment in DS for each loop and restores DS=SS afterward.
 */
extern unsigned char far Dx8[];
#define AT(off) (Dx8[off])
#define AlistT(i) AT((i) + 0x2f62)
#define AlistM(i) AT((i) + 0x2b78)
#define BlistT(i) AT((i) + 0x3d18)
#define BlistM(i) AT((i) + 0x3b22)
#define RlistT(i) AT((i) + 0x46e6)
#define RlistM(i) AT((i) + 0x44f0)
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
static int __based(__segname("PACK")) RecruitPoolTotal;

void far UnRecruit(int all)
{
    int n;
    int i;
    int type;

    n = RecruitPoolTotal;
    if (all == 0)
        n = n / 2;
    else
        n = n + 100;

    i = ListIndexA;
    if (i > 0) {
        while (n > 0) {
            i--;
            type = AlistT(i);
            if (type != 0 && !(type & 0x80)) {
                if (AlistM(i) == 6) {
                    AlistM(i) = 0;
                    n--;
                }
            }
            if (i <= 0)
                break;
        }
    }

    i = ListIndexB;
    if (i > 0) {
        while (n > 0) {
            i--;
            type = BlistT(i);
            if (type != 0 && !(type & 0x80)) {
                if (BlistM(i) == 6) {
                    BlistM(i) = 0;
                    n--;
                }
            }
            if (i <= 0)
                break;
        }
    }

    i = ListIndexR;
    if (i > 0) {
        while (n > 0) {
            i--;
            type = RlistT(i);
            if (type != 0 && !(type & 0x80)) {
                if (RlistM(i) == 6) {
                    RlistM(i) = 7;
                    n--;
                }
            }
            if (i <= 0)
                break;
        }
    }
}
