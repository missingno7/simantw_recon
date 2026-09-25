/*
 * NetworkSend: negotiate a NetBIOS session (NbCall("CLIEANT","SERVANT")
 * with name lengths 0x1e), and if it returns a nonzero session id,
 * receive a command word into result. If that result is negative, skip
 * straight to the closing round. If 0 or 1, send four 0x1000-byte
 * chunks of netBuffer (offsets 0, 0x1000, 0x4000, 0x5000), each
 * followed by an NbReceive except the last, whose NbSend instruction is
 * physically shared (tail-merged by the compiler) with the closing
 * round below. If 2, send chunks at 0x2000 and 0x6000; if 3, send
 * chunks at 0x3000 and 0x7000 (any other result skips directly to the
 * closing round too). Every path converges on one closing round:
 * NbReceive, then NbSend of a private near region (bracketed by two
 * unnamed symbols whose address difference is the transmitted length,
 * an evidence-backed "start"/"end" idiom -- the difference is computed
 * at runtime rather than folded, showing they are not compile-time
 * constant-foldable within one segment), and NbHangUp; the function's
 * own return value is whatever NbHangUp leaves in AX.
 */
/*
 * These four wrappers use the compiler's default (C) calling
 * convention -- confirmed by the "add sp,N" cleanup after every call --
 * so arguments push right to left. Their parameter lists are declared
 * in the reverse of the observed push order (rightmost pushed first)
 * so a natural left-to-right call expression reproduces the exact
 * target byte sequence.
 */
extern int far NbCall(char far *name2, char far *name1, int len2, int len1);
extern int far NbReceive(char session, int far *result, int far *cmd);
extern int far NbSend(unsigned char far *buffer, int length, char session);
extern int far NbHangUp(char session);

extern unsigned char near netBuffer[];
extern unsigned char near finalRegionStart[];
extern unsigned char near finalRegionEnd[];

int far NetworkSend(void)
{
    char retcode;
    int cmd;
    int result;

    retcode = NbCall("SERVANT", "CLIEANT", 0x1e, 0x1e);
    if (retcode != 0) {
        cmd = 2;
        NbReceive(retcode, &result, &cmd);
        if (result >= 0) {
            if (result <= 1) {
                NbSend(netBuffer, 0x1000, retcode);
                cmd = 2;
                NbReceive(retcode, &result, &cmd);
                NbSend(netBuffer + 0x1000, 0x1000, retcode);
                cmd = 2;
                NbReceive(retcode, &result, &cmd);
                NbSend(netBuffer + 0x4000, 0x1000, retcode);
                cmd = 2;
                NbReceive(retcode, &result, &cmd);
                NbSend(netBuffer + 0x5000, 0x1000, retcode);
            } else if (result == 2) {
                NbSend(netBuffer + 0x2000, 0x1000, retcode);
                cmd = 2;
                NbReceive(retcode, &result, &cmd);
                NbSend(netBuffer + 0x6000, 0x1000, retcode);
            } else if (result == 3) {
                NbSend(netBuffer + 0x3000, 0x1000, retcode);
                cmd = 2;
                NbReceive(retcode, &result, &cmd);
                NbSend(netBuffer + 0x7000, 0x1000, retcode);
            }
        }
    }

    cmd = 2;
    NbReceive(retcode, &result, &cmd);
    NbSend(finalRegionStart, finalRegionEnd - finalRegionStart, retcode);
    return NbHangUp(retcode);
}
