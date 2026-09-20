extern int near bigFontH;
extern int near smallFontH;
extern int far pascal DeleteObject(int handle);
extern int far pascal RemoveFontResource(char far *filename);

void GCloseFonts(void)
{
    if (bigFontH)
        DeleteObject(bigFontH);
    if (smallFontH)
        DeleteObject(smallFontH);
    RemoveFontResource("fontres.fon");
}
