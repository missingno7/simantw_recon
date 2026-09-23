/* Insert one string into the decompressor's Okumura LZSS search tree. */
#define N 4096
#define F 18
#define NIL N

extern void far *unpackHandle;
#define MatchPosition ((unsigned int __based((__segment)unpackHandle) *)0)
#define MatchLength ((unsigned int __based((__segment)unpackHandle) *)2)
#define TextBuf ((unsigned char __based((__segment)unpackHandle) *)4)
#define Left ((unsigned int __based((__segment)unpackHandle) *)0x1016)
#define Right ((unsigned int __based((__segment)unpackHandle) *)0x3018)
#define Parent ((unsigned int __based((__segment)unpackHandle) *)0x521a)

void far InsertNode(int r)
{
    int i;
    int p;
    int cmp;

    cmp = 1;
    p = N + 1 + TextBuf[r];
    Right[r] = NIL;
    Left[r] = NIL;
    MatchLength[0] = 0;

    for (;;) {
        if (cmp >= 0) {
            if (Right[p] != NIL) {
                p = Right[p];
            } else {
                Right[p] = r;
                Parent[r] = p;
                return;
            }
        } else {
            if (Left[p] != NIL) {
                p = Left[p];
            } else {
                Left[p] = r;
                Parent[r] = p;
                return;
            }
        }

        for (i = 1; i < F; ++i) {
            cmp = TextBuf[r + i] - TextBuf[p + i];
            if (cmp != 0)
                break;
        }
        if (i > MatchLength[0]) {
            MatchPosition[0] = p;
            if ((MatchLength[0] = i) >= F)
                break;
        }
    }

    Parent[r] = Parent[p];
    Left[r] = Left[p];
    Right[r] = Right[p];
    Parent[Left[p]] = r;
    Parent[Right[p]] = r;
    if (Right[Parent[p]] == p)
        Right[Parent[p]] = r;
    else
        Left[Parent[p]] = r;
    Parent[p] = NIL;
}
