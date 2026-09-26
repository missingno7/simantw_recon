/*
 * Hypothesis: keep filling the configured far unpack buffer from the open
 * handle until Unpack has produced the requested amount.  The positive
 * private count at DGROUP:0xb7c8 means buffered input is already available;
 * otherwise read() refills the private far buffer at 0xb7c4 and records the
 * number of bytes read.  Unpack receives the caller's offset advanced by the
 * bytes already produced, the caller's middle word unchanged, and the
 * remaining requested count.  A non-positive read or an exact total returns
 * the accumulated count.
 */
extern int near unpackHandle;
extern int near unpackRemaining;
extern unsigned int near unpackSize;
extern void far *near unpackBuffer;
extern void far *near unpackReadBuffer;
extern int far read(int handle, void far *buffer, unsigned int size);
extern int near Unpack(int offset, int destination, int amount);

int UnpackFileRead(int offset, int destination, int amount)
{
    int produced;
    int bytes;
    produced = 0;
    if (unpackRemaining > 0)
        goto process;
    goto refill;

process:
    produced += Unpack(offset + produced, destination,
                       amount - produced);
    if (produced != amount)
        goto refill;
    goto done;

refill:
    unpackReadBuffer = unpackBuffer;
    bytes = read(unpackHandle, unpackReadBuffer, unpackSize);
    if (bytes <= 0)
        goto done;
    unpackRemaining = bytes;
    goto process;

done:
    return produced;
}
