extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define ATW(off) (*(int far *)&AT(off))
#define RightD(d)  ATW((d) + 0x1016)
#define LeftD(d)   ATW((d) + 0x3018)
#define ParentD(d) ATW((d) + 0x521a)

#define NIL 0x1000

void far DeleteNode(int n)
{
    int nb;
    int s;
    int sb;
    int t;
    int tb;
    int p;
    int pb;

    nb = n << 1;
    if (ParentD(nb) == NIL)
        return;

    if (LeftD(nb) == NIL) {
        s = RightD(nb);
        sb = s << 1;
    } else if (RightD(nb) == NIL) {
        s = LeftD(nb);
        sb = s << 1;
    } else {
        s = RightD(nb);
        sb = s << 1;
        while (LeftD(sb) != NIL) {
            s = LeftD(sb);
            sb = s << 1;
        }
        t = RightD(sb);
        p = ParentD(sb);
        pb = p << 1;
        LeftD(pb) = t;
        tb = t << 1;
        ParentD(tb) = p;

        t = RightD(nb);
        RightD(sb) = t;
        tb = t << 1;
        ParentD(tb) = s;

        t = LeftD(nb);
        LeftD(sb) = t;
        tb = t << 1;
        ParentD(tb) = s;
    }

    p = ParentD(nb);
    pb = p << 1;
    ParentD(sb) = p;
    if (LeftD(pb) == n)
        LeftD(pb) = s;
    else
        RightD(pb) = s;
    ParentD(nb) = NIL;
}
