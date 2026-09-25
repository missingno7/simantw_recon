extern unsigned long far FlipLong(unsigned long value);

void ExtractDWord(void far * far *p, unsigned long far *out)
{
    *out = *(unsigned long far *)*p;
    *out = FlipLong(*out);
    *p = (void far *)((unsigned long)*p + 4);
}
