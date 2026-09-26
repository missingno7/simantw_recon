/* Remove one string from the Okumura LZSS binary search tree. */
#define N 4096
#define NIL N

struct LzssState {
    int match_position;
    int match_length;
    unsigned char text_buf[N + 18 - 1];
    int lson[N + 1];
    int rson[N + 257];
    int dad[N + 1];
};

extern void far *unpackHandle;
#define lzss ((struct LzssState __based((__segment)unpackHandle) *)0)

void far DeleteNode(int p)
{
    int q;
    int root;

    if (lzss->dad[p] == NIL)
        return;
    if (lzss->lson[p] == NIL)
        q = lzss->rson[p];
    else if (lzss->rson[p] == NIL)
        q = lzss->lson[p];
    else {
        q = lzss->rson[p];
        while (lzss->lson[q] != NIL)
            q = lzss->lson[q];
        if (lzss->dad[q] != p) {
            lzss->lson[lzss->dad[q]] = lzss->rson[q];
            lzss->dad[lzss->rson[q]] = lzss->dad[q];
            lzss->rson[q] = lzss->rson[p];
            lzss->dad[lzss->rson[p]] = q;
        }
        lzss->lson[q] = lzss->lson[p];
        lzss->dad[lzss->lson[p]] = q;
    }

    root = lzss->dad[p];
    lzss->dad[q] = root;
    if (lzss->rson[root] == p)
        lzss->rson[root] = q;
    else
        lzss->lson[root] = q;
    lzss->dad[p] = NIL;
}
