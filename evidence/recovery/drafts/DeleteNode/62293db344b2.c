#define N 4096
#define F 18
#define NIL N
extern void far * near unpackHandle;
extern int __based((__segment)unpackHandle) match_position;
extern int __based((__segment)unpackHandle) match_length;
extern unsigned char __based((__segment)unpackHandle) text_buf[];
extern int __based((__segment)unpackHandle) lson[];
extern int __based((__segment)unpackHandle) rson[];
extern int __based((__segment)unpackHandle) dad[];

void far InitTree(void)
{
    int i;
    for (i = N + 1; i <= N + 256; ++i) rson[i] = NIL;
    for (i = 0; i < N; ++i) dad[i] = NIL;
}

void far InsertNode(int r)
{
    int i, p, cmp;
    unsigned char far *key;
    cmp = 1;
    key = (unsigned char far *)text_buf + r;
    p = N + 1 + key[0];
    rson[r] = NIL;
    lson[r] = NIL;
    match_length = 0;
    for (;;) {
        if (cmp >= 0) {
            if (rson[p] != NIL) p = rson[p];
            else { rson[p] = r; dad[r] = p; return; }
        } else {
            if (lson[p] != NIL) p = lson[p];
            else { lson[p] = r; dad[r] = p; return; }
        }
        for (i = 1; i < F; ++i) {
            cmp = key[i] - text_buf[p + i];
            if (cmp != 0) break;
        }
        if (i > match_length) {
            match_position = p;
            if ((match_length = i) >= F) break;
        }
    }
    dad[r] = dad[p];
    lson[r] = lson[p];
    rson[r] = rson[p];
    dad[lson[p]] = r;
    dad[rson[p]] = r;
    if (rson[dad[p]] == p) rson[dad[p]] = r;
    else lson[dad[p]] = r;
    dad[p] = NIL;
}

void far DeleteNode(int p)
{
    int q, r;
    if (dad[p] == NIL) return;
    if (lson[p] == NIL) q = rson[p];
    else if (rson[p] == NIL) q = lson[p];
    else {
        q = lson[p];
        if (rson[q] != NIL) {
            do { q = rson[q]; } while (rson[q] != NIL);
            r = dad[q];
            rson[r] = lson[q];
            dad[lson[q]] = r;
            lson[q] = lson[p];
            dad[lson[p]] = q;
        }
        rson[q] = rson[p];
        dad[rson[p]] = q;
    }
    dad[q] = dad[p];
    if (rson[dad[p]] == p) rson[dad[p]] = q;
    else lson[dad[p]] = q;
    dad[p] = NIL;
}
