/* Candidate translation unit text_7486_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _NbCall
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern void *memset(void *, int, unsigned);
extern unsigned strlen(const char far *);
extern void *memcpy(void *, const void far *, unsigned);
extern void far NetBios(void far *ncb);
extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];


void far pool_literal_fill_1EC2(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_literal_fill_1EC2)

/* SCAFFOLD, not recovered source: body literals between _NbCall and _NbCall (DGROUP 1EC2-1F22), unclaimed members' body literals. */
void far pool_literal_fill_1EC2(void)
{
    volatile char far *p;

    p = "\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\045\163\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\101\144\141\160\164\145\162\040\155\141\154\146\165\156\143\164\151\157\156\056\012\000\116\145\164\102\111\117\123\040\122\145\164\103\157\144\145\050\045\043\170\051\072\040\045\163\012";
}

unsigned char far NbCall(char far *local_name, char far *remote_name,
                unsigned char session, unsigned char number)
{
    unsigned char ncb[64];
    int length;
    int i;

    memset(ncb, 0, 64);
    ncb[0] = 0x10;
    memset(&ncb[0x0a], 0x20, 16);
    length = strlen(remote_name);
    if (length > 16)
        length = 16;
    memcpy(&ncb[0x0a], remote_name, length);
    ncb[0x19] = 0;

    memset(&ncb[0x1a], 0x20, 16);
    length = strlen(local_name);
    if (length > 16)
        length = 16;
    memcpy(&ncb[0x1a], local_name, length);
    ncb[0x29] = 0;

    ncb[0x2a] = session;
    ncb[0x2b] = number;
    NetBios(ncb);
    DebugWinPrintf("NetBIOS: Call.\n");
    if (ncb[0x31] < 0x50)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31]]);
    else if (ncb[0x31] < 0xf0)
        DebugWinPrintf("NetBIOS Final RetCode(%#x): Adapter malfunction.\n", ncb[0x31]);
    else
        DebugWinPrintf("NetBIOS Final RetCode(%#x): %s\n", ncb[0x31],
                       (char far *)NB_RETCODE[ncb[0x31] - 0xa0]);
    if (ncb[0x31] == 0)
        return ncb[2];
    return 0;
}

