/* Candidate translation unit text_7C70_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _NbHangUp
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern void *memset(void *, int, unsigned);
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];


void far pool_data_fill_1E6E(void);
void far pool_data_fill_1E8A(void);
void far pool_data_fill_1EC0(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_1E6E)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_1E8A)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_1EC0)

/* SCAFFOLD, not recovered source: the 2 bytes of private data between _NbHangUp and _NbHangUp (DGROUP 1E6E-1E70, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_1E6E(void)
{
    volatile char far *p;

    p = "\012";
}

/* SCAFFOLD, not recovered source: the 24 bytes of private data between _NbHangUp and _NbHangUp (DGROUP 1E8A-1EA2, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_1E8A(void)
{
    volatile char far *p;

    p = "\072\040\101\144\141\160\164\145\162\040\155\141\154\146\165\156\143\164\151\157\156\056\012";
}

/* SCAFFOLD, not recovered source: the 282 bytes of private data between _NbHangUp and _NbHangUp (DGROUP 1EC0-1FDA, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_1EC0(void)
{
    volatile char far *p;

    p = "\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\045\163\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\101\144\141\160\164\145\162\040\155\141\154\146\165\156\143\164\151\157\156\056\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\045\163\012\000\116\145\164\102\111\117\123\072\040\103\141\154\154\056\012\000\116\145\164\102\111\117\123\072\040\101\144\144\116\141\155\145\056\012\000\116\145\164\102\111\117\123\072\040\122\145\163\145\164\056\012\000\116\145\164\102\111\117\123\072\040\123\145\156\144\056\012\000\116\145\164\102\111\117\123\072\040\114\151\163\164\145\156\050\045\163\051\056\012\000\116\145\164\102\111\117\123\072\040\120\157\163\164\114\151\163\164\145\156\050\045\163\051\056\012\000\116\145\164\102\111\117\123\072\040\104\145\154\145\164\145\040\116\141\155\145\056\012\000\116\145\164\102\111\117\123\072\040\122\145\143\145\151\166\145\056\012\000\116\145\164\102\111\117\123\072\040\120\157\163\164\122\145\143\145\151\166\145\101\156\171\056\012";
}

void far NbHangUp(unsigned char session)
{
    unsigned char ncb[64];
    memset(ncb, 0, 64);
    ncb[0] = 0x12;
    ncb[2] = session;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS hang up");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS hang up status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS hang up status %u", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS hang up status %u: %s", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
}

