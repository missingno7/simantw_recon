/* Candidate translation unit text_7706_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _NbSend
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern void *memset(void *, int, unsigned);
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];


void far pool_literal_fill_1EC2(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_literal_fill_1EC2)

/* SCAFFOLD, not recovered source: body literals between _NbSend and _NbSend (DGROUP 1EC2-1F56), unclaimed members' body literals. */
void far pool_literal_fill_1EC2(void)
{
    volatile char far *p;

    p = "\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\045\163\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\101\144\141\160\164\145\162\040\155\141\154\146\165\156\143\164\151\157\156\056\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\045\163\012\000\116\145\164\102\111\117\123\072\040\103\141\154\154\056\012\000\116\145\164\102\111\117\123\072\040\101\144\144\116\141\155\145\056\012\000\116\145\164\102\111\117\123\072\040\122\145\163\145\164\056\012";
}

void far NbSend(unsigned char far *buffer, unsigned int length,
                unsigned char session)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x14;
    ncb[2] = session;
    *(unsigned char far **)&ncb[4] = buffer;
    *(unsigned int far *)&ncb[8] = length;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Send.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): Adapter malfunction.\n", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}

