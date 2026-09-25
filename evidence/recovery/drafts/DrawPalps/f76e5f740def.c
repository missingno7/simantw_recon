/* Draw both palp curves around the spider head. Direction selects one of
 * eight axis/sign arrangements; a small per-frame sample is used only in
 * modes that animate the mouthparts. */
extern int far SMode;
extern int far MeSMode;
extern int far MeMode;
extern int far SRand1(int range);
extern int far ConvColor(int color);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void near ed_LineTo(int x, int y);

extern int far editBufInvalidFlag[];
extern int near edata[];
extern char far PyT[];
extern char far PxT[];
extern char far PyT2[];
extern char far PxT2[];
extern char far PyD[];
extern char far PxD[];
extern char far PyD2[];
extern char far PxD2[];

void far DrawPalps(int x, int y, int direction)
{
    int sample;

    if (SMode > 1 || MeSMode >= 6)
        sample = SRand1(4);
    else
        sample = 0;

    if (MeMode == 1)
        GSetAttrib(0, 0, 1);
    else
        GSetAttrib(0, 0, ConvColor(15));

    switch (direction) {
    case 0:
        editBufInvalidFlag[-3] = x + 4;
        edata[57] = y - 10;
        ed_LineTo(x + PxT[sample], y + PyT[sample]);
        ed_LineTo(x + PxT2[sample], y + PyT2[sample]);
        editBufInvalidFlag[-3] = x - 4;
        edata[57] = y - 10;
        ed_LineTo(x - PxT[sample], y + PyT[sample]);
        ed_LineTo(x - PxT2[sample], y - PyT2[sample]);
        break;
    case 1:
        editBufInvalidFlag[-3] = x + 10;
        edata[57] = y - 3;
        ed_LineTo(x + PxD[sample], y + PyD[sample]);
        ed_LineTo(x + PxD2[sample], y + PyD2[sample]);
        editBufInvalidFlag[-3] = x + 3;
        edata[57] = y - 10;
        ed_LineTo(x - PyD[sample], y - PxD[sample]);
        ed_LineTo(x - PyD2[sample], y - PxD2[sample]);
        break;
    case 2:
        editBufInvalidFlag[-3] = x + 10;
        edata[57] = y - 4;
        ed_LineTo(x - PyT[sample], y - PxT[sample]);
        ed_LineTo(x - PyT2[sample], y - PxT2[sample]);
        editBufInvalidFlag[-3] = x + 10;
        edata[57] = y + 4;
        ed_LineTo(x - PyT[sample], y + PxT[sample]);
        ed_LineTo(x - PyT2[sample], y + PxT2[sample]);
        break;
    case 3:
        editBufInvalidFlag[-3] = x + 10;
        edata[57] = y + 3;
        ed_LineTo(x + PxD[sample], y - PyD[sample]);
        ed_LineTo(x + PxD2[sample], y - PyD2[sample]);
        editBufInvalidFlag[-3] = x + 3;
        edata[57] = y + 10;
        ed_LineTo(x - PyD[sample], y + PxD2[sample]);
        ed_LineTo(x - PyD2[sample], y + PxD2[sample]);
        break;
    case 4:
        editBufInvalidFlag[-3] = x + 4;
        edata[57] = y + 10;
        ed_LineTo(x + PxT[sample], y - PyT[sample]);
        ed_LineTo(x + PxT2[sample], y - PyT2[sample]);
        editBufInvalidFlag[-3] = x - 4;
        edata[57] = y + 10;
        ed_LineTo(x - PxT[sample], y - PyT[sample]);
        ed_LineTo(x - PxT2[sample], y - PyT2[sample]);
        break;
    case 5:
        editBufInvalidFlag[-3] = x - 10;
        edata[57] = y + 3;
        ed_LineTo(x - PxD[sample], y - PyD[sample]);
        ed_LineTo(x - PxD2[sample], y - PyD2[sample]);
        editBufInvalidFlag[-3] = x - 3;
        edata[57] = y + 10;
        ed_LineTo(x + PyD[sample], y + PxD[sample]);
        ed_LineTo(x + PyD2[sample], y + PxD2[sample]);
        break;
    case 6:
        editBufInvalidFlag[-3] = x - 10;
        edata[57] = y - 4;
        ed_LineTo(x + PyT[sample], y - PxT[sample]);
        ed_LineTo(x + PyT2[sample], y - PxT2[sample]);
        editBufInvalidFlag[-3] = x - 10;
        edata[57] = y + 4;
        ed_LineTo(x + PyT[sample], y + PxT[sample]);
        ed_LineTo(x + PyT2[sample], y + PxT2[sample]);
        break;
    case 7:
        editBufInvalidFlag[-3] = x - 10;
        edata[57] = y - 3;
        ed_LineTo(x - PxD[sample], y + PyD[sample]);
        ed_LineTo(x - PxD2[sample], y + PyD2[sample]);
        editBufInvalidFlag[-3] = x - 3;
        edata[57] = y - 10;
        ed_LineTo(x + PyD[sample], y - PxD[sample]);
        ed_LineTo(x + PyD2[sample], y - PxD2[sample]);
        break;
    }
}
