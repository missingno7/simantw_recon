/* MSC's far-copy intrinsic should select the word and odd-byte REP sequence. */
extern void far *_fmemcpy(void far *destination, const void far *source,
                          unsigned int count);

void far BlockMove(void far *source, void far *destination,
                   unsigned int count)
{
    (void)_fmemcpy(destination, source, count);
}
