extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define ATW(off) (*(int far *)&AT(off))
#define Right(i)  ATW((i) * 2 + 0x1016)
#define Left(i)   ATW((i) * 2 + 0x3018)
#define Parent(i) ATW((i) * 2 + 0x521a)

#define NIL 0x1000

void far DeleteNode(int n)
{
    int s;
    int p;
    int r;

    if (Parent(n) == NIL)
        return;

    if (Left(n) == NIL) {
        s = Right(n);
    } else if (Right(n) == NIL) {
        s = Left(n);
    } else {
        s = Right(n);
        while (Left(s) != NIL)
            s = Left(s);
        r = Right(s);
        p = Parent(s);
        Left(p) = r;
        Parent(r) = p;
        Right(s) = Right(n);
        Parent(Right(n)) = s;
        Left(s) = Left(n);
        Parent(Left(n)) = s;
    }

    p = Parent(n);
    Parent(s) = p;
    if (Left(p) == n)
        Left(p) = s;
    else
        Right(p) = s;
    Parent(n) = NIL;
}
