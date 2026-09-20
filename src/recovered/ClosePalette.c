extern int near paletteH;
extern int far pascal DeleteObject(int handle);

void ClosePalette(void)
{
    if (paletteH) {
        DeleteObject(paletteH);
        paletteH = 0;
    }
}
