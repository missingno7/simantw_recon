/*
 * DeleteNode: the LZSS (Okumura) binary-tree deletion for the unpacker.
 * The tree lives in the far block whose far pointer is unpackHandle: the
 * 4113-byte text buffer is followed by lson[N+1] at 0x1016, rson[N+257]
 * at 0x3018 and dad[N+1] at 0x521a (N = 4096, NIL = N).  The arrays are
 * addressed through the block's segment (DS is loaded from the pointer's
 * segment word for the whole function) at those fixed offsets.  Node p
 * is unlinked: a node with one child is replaced by it; otherwise the
 * rightmost node of the left subtree takes its place.
 */
#define N 4096
#define NIL N

extern void far * near unpackHandle;

#define lson (((int __based((__segment)unpackHandle) *)0x1016))
#define rson (((int __based((__segment)unpackHandle) *)0x3018))
#define dad (((int __based((__segment)unpackHandle) *)0x521a))

void far DeleteNode(int p)
{
    int q;

    if (dad[p] == NIL)
        return;
    if (rson[p] == NIL)
        q = lson[p];
    else if (lson[p] == NIL)
        q = rson[p];
    else {
        q = lson[p];
        if (rson[q] != NIL) {
            do {
                q = rson[q];
            } while (rson[q] != NIL);
            rson[dad[q]] = lson[q];
            dad[lson[q]] = dad[q];
            lson[q] = lson[p];
            dad[lson[p]] = q;
        }
        rson[q] = rson[p];
        dad[rson[p]] = q;
    }
    dad[q] = dad[p];
    if (rson[dad[p]] == p)
        rson[dad[p]] = q;
    else
        lson[dad[p]] = q;
    dad[p] = NIL;
}
