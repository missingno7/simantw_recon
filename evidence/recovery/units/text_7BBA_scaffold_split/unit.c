/* Candidate translation unit text_7BBA_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _NbPostReceiveAny
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern void *memset(void *, int, unsigned);
extern void far NetBios(unsigned char far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
static unsigned char near postReceiveNcb[64];


void far pool_literal_fill_1F22(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_literal_fill_1F22)

/* SCAFFOLD, not recovered source: body literals between _NbPostReceiveAny and _NbPostReceiveAny (DGROUP 1F22-1FC0), unclaimed members' body literals. */
void far pool_literal_fill_1F22(void)
{
    volatile char far *p;

    p = "\116\145\164\102\111\117\123\072\040\103\141\154\154\056\012\000\116\145\164\102\111\117\123\072\040\101\144\144\116\141\155\145\056\012\000\116\145\164\102\111\117\123\072\040\122\145\163\145\164\056\012\000\116\145\164\102\111\117\123\072\040\123\145\156\144\056\012\000\116\145\164\102\111\117\123\072\040\114\151\163\164\145\156\050\045\163\051\056\012\000\116\145\164\102\111\117\123\072\040\120\157\163\164\114\151\163\164\145\156\050\045\163\051\056\012\000\116\145\164\102\111\117\123\072\040\104\145\154\145\164\145\040\116\141\155\145\056\012\000\116\145\164\102\111\117\123\072\040\122\145\143\145\151\166\145\056\012";
}

unsigned int far NbPostReceiveAny(unsigned char session,
                                  unsigned char far *buffer,
                                  unsigned int length,
                                  unsigned long timeout)
{
    memset(postReceiveNcb, 0, 64);

    postReceiveNcb[0] = 0x96;
    postReceiveNcb[3] = session;
    *(unsigned char far **)&postReceiveNcb[4] = buffer;
    *(unsigned int far *)&postReceiveNcb[8] = length;
    *(unsigned long far *)&postReceiveNcb[0x2c] = timeout;
    NetBios(postReceiveNcb);
    DebugWinPrintf("NetBIOS: PostReceiveAny.\n");

    if (postReceiveNcb[1] < 0x50)
        DebugWinPrintf("NetBIOS RetCode(%#x): %s\n", postReceiveNcb[1],
                       (char far *)NB_RETCODE[postReceiveNcb[1]]);
    else if (postReceiveNcb[1] < 0xf0)
        DebugWinPrintf("NetBIOS RetCode(%#x): Adapter malfunction.\n", postReceiveNcb[1]);
    else
        DebugWinPrintf("NetBIOS RetCode(%#x): %s\n", postReceiveNcb[1],
                       (char far *)NB_RETCODE[postReceiveNcb[1] - 0xa0]);

    return postReceiveNcb[1];
}

