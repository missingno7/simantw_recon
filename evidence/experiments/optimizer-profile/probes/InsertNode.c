/* Insert one string in the Okumura LZSS binary search tree. */
#define N 4096
#define F 18
#define NIL N

struct LzssState {
    int match_position;
    int match_length;
    unsigned char text_buf[N + F - 1];
    int lson[N + 1];
    int rson[N + 257];
    int dad[N + 1];
};

extern void far *unpackHandle;
#define lzss ((struct LzssState __based((__segment)unpackHandle) *)0)

void far InsertNode(int r)
{
    int i;
    int p;
    int cmp;
    unsigned char far *key;

    cmp = 1;
    key = (unsigned char far *)lzss->text_buf + r;
    p = N + 1 + key[0];
    lzss->rson[r] = NIL;
    lzss->lson[r] = NIL;
    lzss->match_length = 0;

    for (;;) {
        if (cmp >= 0) {
            if (lzss->rson[p] != NIL)
                p = lzss->rson[p];
            else {
                lzss->rson[p] = r;
                lzss->dad[r] = p;
                return;
            }
        } else {
            if (lzss->lson[p] != NIL)
                p = lzss->lson[p];
            else {
                lzss->lson[p] = r;
                lzss->dad[r] = p;
                return;
            }
        }

        for (i = 1; i < F; ++i) {
            cmp = key[i] - lzss->text_buf[p + i];
            if (cmp != 0)
                break;
        }
        if (i > lzss->match_length) {
            lzss->match_position = p;
            if ((lzss->match_length = i) >= F)
                break;
        }
    }

    lzss->dad[r] = lzss->dad[p];
    lzss->lson[r] = lzss->lson[p];
    lzss->rson[r] = lzss->rson[p];
    lzss->dad[lzss->lson[p]] = r;
    lzss->dad[lzss->rson[p]] = r;
    if (lzss->rson[lzss->dad[p]] == p)
        lzss->rson[lzss->dad[p]] = r;
    else
        lzss->lson[lzss->dad[p]] = r;
    lzss->dad[p] = NIL;
}
