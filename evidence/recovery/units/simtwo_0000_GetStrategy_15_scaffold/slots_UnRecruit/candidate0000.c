/* Candidate translation unit simtwo_0000_Recruit_3: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _Recruit, _UnRecruit, _RecruitRed */

extern unsigned char far Dx8[];
#define AT(off) (Dx8[off])
#define AlistT(i) AT((i) + 0x2f62)
#define AlistM(i) AT((i) + 0x2b78)
#define AlistS(i) AT((i) + 0x334c)
#define BlistT(i) AT((i) + 0x3d18)
#define BlistM(i) AT((i) + 0x3b22)
#define BlistS(i) AT((i) + 0x3f0e)
extern int far ListIndexA;
extern int far ListIndexB;
#define RlistT(i) AT((i) + 0x46e6)
#define RlistM(i) AT((i) + 0x44f0)
extern int far ListIndexR;
static int __based(__segname("PACK")) RecruitPoolTotal;

void far Recruit(int count)
{
    int i;
    int n;
    int type;
    int caste;

    n = count;
    i = ListIndexA;
    while (i > 0) {
        if (n <= 0)
            break;
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
    i = ListIndexB;
    while (i > 0) {
        if (n <= 0)
            break;
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

void far RecruitRed(int count)
{
    int cur;
    int need;
    int i;
    int type;
    int mode;

    need = count;
    i = ListIndexA;
    while (i > 0 && need > 0) {
        i--;
        type = Dx8[i + 0x2f62];
        if (type != 0 && type > 0x7f) {
            cur = Dx8[i + 0x2b78];
            mode = (type & 0x78) >> 3;
            if (mode == 2 || mode == 6) {
                if (cur != 0x13 && cur != 6) {
                    Dx8[i + 0x2b78] = 6;
                    Dx8[i + 0x334c] = 0;
                    need--;
                }
            }
        }
    }
}

