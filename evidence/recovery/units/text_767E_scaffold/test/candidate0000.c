/* Candidate translation unit text_767E_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _NbReset
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern void *memset(void *, int, unsigned);
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];


void far pool_data_fill_1EC2(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_1EC2)

/* SCAFFOLD, not recovered source: the 131 bytes of private data between _NbReset and _NbReset (DGROUP 1EC2-1F45, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_1EC2(void)
{
    volatile char far *p;

    p = "\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\045\163\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\101\144\141\160\164\145\162\040\155\141\154\146\165\156\143\164\151\157\156\056\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\045\163\012\000\116\145\164\102\111\117\123\072\040\103\141\154\154\056\012\000\116\145\164\102\111\117\123\072\040\101\144\144\116\141\155\145\056\012";
}

unsigned int far NbReset(void)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x32;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Reset.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): Adapter malfunction.\n", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}

