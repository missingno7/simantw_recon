/* Candidate translation unit text_7370_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _NbFinalStatus
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern void far DebugWinPrintf(char far *format, ...);
extern char __based(__segname("SIMANT_DATA_GROUP")) NB_RETCODE[128][60];
struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediate_status;
    unsigned char reserved[0x2f];
    unsigned char final_status;
};


void far pool_literal_fill_1E6C(void);
void far pool_literal_fill_1E88(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_literal_fill_1E6C)
#pragma alloc_text(POOLSTUB_TEXT, pool_literal_fill_1E88)

/* SCAFFOLD, not recovered source: body literals between _NbFinalStatus and _NbFinalStatus (DGROUP 1E6C-1E70), unclaimed members' body literals. */
void far pool_literal_fill_1E6C(void)
{
    volatile char far *p;

    p = "\045\163\012";
}

/* SCAFFOLD, not recovered source: body literals between _NbFinalStatus and _NbFinalStatus (DGROUP 1E88-1EA2), unclaimed members' body literals. */
void far pool_literal_fill_1E88(void)
{
    volatile char far *p;

    p = "\170\051\072\040\101\144\141\160\164\145\162\040\155\141\154\146\165\156\143\164\151\157\156\056\012";
}

void far NbFinalStatus(struct NetbiosControlBlock far *ncb)
{
    union StatusSlot { unsigned short whole; unsigned char value; } statusSlot;

    statusSlot.value = ncb->final_status;
    if (statusSlot.value < 0x50)
        DebugWinPrintf("NetBIOS final status %u: %s", statusSlot.value,
                       (char far *)NB_RETCODE[statusSlot.value]);
    else if (ncb->final_status < 0xf0)
        DebugWinPrintf("NetBIOS final status %u", statusSlot.value);
    else
        DebugWinPrintf("NetBIOS final status %u: %s", statusSlot.value,
                       (char far *)NB_RETCODE[statusSlot.value - 0xa0]);
}

