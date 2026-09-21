extern unsigned char far Dx8;
#define Right(n) (((int far *)&Dx8)[(n) + 0x80b])
#define Left(n)  (((int far *)&Dx8)[(n) + 0x180c])
#define Parent(n) (((int far *)&Dx8)[(n) + 0x290d])

#define NIL 0x1000

void far DeleteNode(int n)
{
    int id;
    int s;
    int t;

    id = n;

    if (Parent(id) == NIL)
        return;

    if (Left(id) == NIL) {
        s = Right(id);
    } else if (Right(id) == NIL) {
        s = Left(id);
    } else {
        s = Right(id);
        while (Left(s) != NIL)
            s = Left(s);
        t = Right(s);
        Left(Parent(s)) = t;
        Parent(t) = Parent(s);
        Right(s) = Right(id);
        Parent(Right(id)) = s;
        Left(s) = Left(id);
        Parent(Left(id)) = s;
    }

    t = Parent(id);
    Parent(s) = t;
    if (Left(t) == id)
        Left(t) = s;
    else
        Right(t) = s;
    Parent(id) = NIL;
}
