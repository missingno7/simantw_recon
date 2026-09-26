/* Initialize the Okumura LZSS tree sentinel tables. */
#define N 4096
#define NIL N

extern int far match_position;
extern int far match_length;
extern unsigned char far text_buf[N + 18 - 1];
extern int far lson[N + 1];
extern int far rson[N + 257];
extern int far dad[N + 1];

void far InitTree(void)
{
    int i;

    for (i = N + 1; i <= N + 256; ++i)
        rson[i] = NIL;
    for (i = 0; i < N; ++i)
        dad[i] = NIL;
}
