extern unsigned char far Dx8;
#define Right(n) (((int far *)&Dx8)[(n) + 0x80b])
#define Left(n) (((int far *)&Dx8)[(n) + 0x180c])
#define Parent(n) (((int far *)&Dx8)[(n) + 0x290d])

#define NIL 0x1000

void far DeleteNode(int n)
{
    int s;
    int t;

    if (Parent(n) == NIL)
        return;

    if (Left(n) == NIL) {
        s = Right(n);
    } else if (Right(n) == NIL) {
        s = Left(n);
    } else {
        s = Right(n);
        if (Left(s) != NIL) {
            do {
                s = Left(s);
            } while (Left(s) != NIL);
        }
        t = Right(s);
        Left(Parent(s)) = t;
        Parent(t) = Parent(s);
        Right(s) = Right(n);
        Parent(Right(n)) = s;
        Left(s) = Left(n);
        Parent(Left(n)) = s;
    }

    t = Parent(n);
    Parent(s) = t;
    if (Left(t) == n)
        Left(t) = s;
    else
        Right(t) = s;
    Parent(n) = NIL;
}
