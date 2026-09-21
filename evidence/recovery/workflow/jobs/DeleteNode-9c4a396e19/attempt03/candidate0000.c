extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define ATW(off) (*(int far *)&AT(off))
#define RightD(d)  ATW((d) + 0x1016)
#define LeftD(d)   ATW((d) + 0x3018)
#define ParentD(d) ATW((d) + 0x521a)

#define NIL 0x1000

void far DeleteNode(int n)
{
    int b;
    int sb;
    int s;
    int t;
    int w;

    b = n << 1;
    if (ParentD(b) == NIL)
        return;

    if (LeftD(b) == NIL) {
        s = RightD(b);
        sb = s << 1;
    } else if (RightD(b) == NIL) {
        s = LeftD(b);
        sb = s << 1;
    } else {
        s = RightD(b);
        sb = s << 1;
        while (LeftD(sb) != NIL) {
            s = LeftD(sb);
            sb = s << 1;
        }
        t = RightD(sb);
        w = ParentD(sb);
        s = w;
        w <<= 1;
        LeftD(w) = t;
        w = t << 1;
        ParentD(w) = s;

        w = RightD(b);
        RightD(sb) = w;
        w <<= 1;
        s = sb >> 1;
        ParentD(w) = s;

        w = LeftD(b);
        LeftD(sb) = w;
        w <<= 1;
        ParentD(w) = s;
    }

    w = ParentD(b);
    ParentD(sb) = w;
    w <<= 1;
    t = b >> 1;
    if (LeftD(w) == t)
        LeftD(w) = s;
    else
        RightD(w) = s;
    ParentD(b) = NIL;
}
