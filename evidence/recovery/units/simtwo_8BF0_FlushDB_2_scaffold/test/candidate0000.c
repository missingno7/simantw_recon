/* Candidate translation unit simtwo_8BF0_FlushDB_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _FlushDB, _DosPunt
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern int near errno;
extern char far * near sys_errlist[];
extern void far Punt(char far *message, ...);


void far pool_data_fill_B4F8(void);
void DosPunt(int first, int second);

#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_B4F8)
#pragma alloc_text(RUN2_TEXT, DosPunt)

void FlushDB(void) {}

/* SCAFFOLD, not recovered source: the 114 bytes of private data between _DosPunt and _DosPunt (DGROUP B4F8-B56A, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_B4F8(void)
{
    volatile char far *p;

    p = "\040\040\131\157\165\040\156\145\145\144\040\141\040\163\164\141\164\145\155\145\156\164\040\047\106\111\114\105\123\075\061\062\047\040\151\156\012\171\157\165\162\040\143\157\156\146\151\147\056\163\171\163\040\146\151\154\145\056\040\040\120\154\145\141\163\145\040\162\145\146\145\162\040\164\157\040\171\157\165\162\040\144\157\163\040\155\141\156\165\141\154\012\146\157\162\040\155\157\162\145\040\151\156\146\157\162\155\141\164\151\157\156\056";
}

void DosPunt(int first, int second)
{
    if (errno == 0x18) {
        Punt("Too many open files");
    }
    Punt("DOS error %d: %s (%d, %d)", first, second, errno,
         sys_errlist[errno]);
}

