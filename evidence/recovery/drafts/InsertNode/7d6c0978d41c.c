/* Insert one string into the decompressor's Okumura LZSS search tree. */
#define N 4096
#define F 18
#define NIL N

struct LzssState {
    unsigned int matchPosition;
    unsigned int matchLength;
    unsigned char textBuf[N + F];
    unsigned int left[N + 1];
    unsigned int right[N + 257];
    unsigned int parent[N + 1];
};

extern void far *unpackHandle;
#define tree ((struct LzssState __based((__segment)unpackHandle) *)0)

void far InsertNode(int r)
{
    int i;
    int p;
    int cmp;
    unsigned char far *key;

    cmp = 1;
    key = (unsigned char far *)tree->textBuf + r;
    p = N + 1 + key[0];
    tree->right[r] = NIL;
    tree->left[r] = NIL;
    tree->matchLength = 0;

    for (;;) {
        if (cmp >= 0) {
            if (tree->right[p] != NIL) {
                p = tree->right[p];
            } else {
                tree->right[p] = r;
                tree->parent[r] = p;
                return;
            }
        } else {
            if (tree->left[p] != NIL) {
                p = tree->left[p];
            } else {
                tree->left[p] = r;
                tree->parent[r] = p;
                return;
            }
        }

        for (i = 1; i < F; ++i) {
            cmp = key[i] - tree->textBuf[p + i];
            if (cmp != 0)
                break;
        }
        if (i > tree->matchLength) {
            tree->matchPosition = p;
            if ((tree->matchLength = i) >= F)
                break;
        }
    }

    tree->parent[r] = tree->parent[p];
    tree->left[r] = tree->left[p];
    tree->right[r] = tree->right[p];
    tree->parent[tree->left[p]] = r;
    tree->parent[tree->right[p]] = r;
    if (tree->right[tree->parent[p]] == p)
        tree->right[tree->parent[p]] = r;
    else
        tree->left[tree->parent[p]] = r;
    tree->parent[p] = NIL;
}
