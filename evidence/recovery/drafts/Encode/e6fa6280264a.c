/* _Encode: LZSS source hypothesis. PACK's named symbols and the private
 * segment-9 word at offset 2 follow the packet's selector/operand evidence. */
#define N 0x1000
#define F 0x12
#define THRESHOLD 2

extern unsigned char far pack_buf[];
extern int far match_position;
extern int __based(__segname("PACK")) match_length;
extern int near pack_threshold;
extern void near InitTree(void);
extern int near PackReadByte(void);
extern void near PackWriteByte(int value);
extern void near InsertNode(int node);
extern void near DeleteNode(int node);
extern void near PackFinish(void);

void far Encode(void)
{
    int i;
    int c;
    int len;
    int r;
    int s;
    int last;
    int code_ptr;
    int match_len;
    unsigned char mask;
    unsigned char code_buf[0x26];

    InitTree();
    for (i = 0; i < N - F; ++i)
        pack_buf[i] = 0x20;

    s = 0;
    r = N - F;
    len = 0;
    while (len < F) {
        c = PackReadByte();
        if (c == -1)
            break;
        pack_buf[r + len] = (unsigned char)c;
        ++len;
    }
    if (len == 0)
        goto finish;

    for (i = 1; i <= F; ++i)
        InsertNode(r - i);
    InsertNode(r);

    code_buf[0] = 0;
    code_ptr = 1;
    mask = 1;
    do {
        match_len = match_length;
        if (match_len > len)
            match_len = len;
        if (match_len <= THRESHOLD) {
            match_len = 1;
            code_buf[0] |= mask;
            code_buf[code_ptr++] = pack_buf[r];
        } else {
            code_buf[code_ptr++] = (unsigned char)match_position;
            code_buf[code_ptr++] = (unsigned char)(((match_position >> 4) & 0xf0) |
                                                      (match_len - (THRESHOLD + 1)));
        }
        mask <<= 1;
        if (mask == 0) {
            for (i = 0; i < code_ptr; ++i)
                PackWriteByte(code_buf[i]);
            code_buf[0] = 0;
            code_ptr = 1;
            mask = 1;
        }

        last = match_len;
        for (i = 0; i < last; ++i) {
            c = PackReadByte();
            if (c == -1)
                break;
            DeleteNode(s);
            pack_buf[s] = (unsigned char)c;
            if (s < F - 1)
                pack_buf[s + N] = (unsigned char)c;
            s = (s + 1) & (N - 1);
            r = (r + 1) & (N - 1);
            InsertNode(r);
        }
        while (i++ < last) {
            DeleteNode(s);
            s = (s + 1) & (N - 1);
            r = (r + 1) & (N - 1);
            if (--len)
                InsertNode(r);
        }
    } while (len > 0);

    if (code_ptr > 1) {
        for (i = 0; i < code_ptr; ++i)
            PackWriteByte(code_buf[i]);
    }
finish:
    PackFinish();
}
