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
    int baseX = x;
    int baseY = y;
    register int sample;
    int requestedDirection;
    requestedDirection = direction;
    if (SMode > 1 || MeSMode >= 6)
        sample = SRand1(4);
    else
        sample = 0;

    if (MeMode == 1)
        GSetAttrib(1, 0, 0);
    else
        GSetAttrib(ConvColor(15), 0, 0);

    switch (requestedDirection) {
    case 0:
        editBufInvalidFlag[-3] = baseX + 4;
        edata[57] = baseY - 10;
        ed_LineTo(baseX + PxT[sample], baseY + PyT[sample]);
        ed_LineTo(baseX + PxT2[sample], baseY + PyT2[sample]);
        editBufInvalidFlag[-3] = baseX - 4;
        edata[57] = baseY - 10;
        ed_LineTo(baseX - PxT[sample], baseY + PyT[sample]);
        ed_LineTo(baseX - PxT2[sample], baseY + PyT2[sample]);
        break;
    case 1:
        editBufInvalidFlag[-3] = baseX + 10;
        edata[57] = baseY - 3;
        ed_LineTo(baseX + PxD[sample], baseY + PyD[sample]);
        ed_LineTo(baseX + PxD2[sample], baseY + PyD2[sample]);
        editBufInvalidFlag[-3] = baseX + 3;
        edata[57] = baseY - 10;
        ed_LineTo(baseX - PyD[sample], baseY - PxD[sample]);
        ed_LineTo(baseX - PyD2[sample], baseY - PxD2[sample]);
        break;
    case 2:
        editBufInvalidFlag[-3] = baseX + 10;
        edata[57] = baseY - 4;
        ed_LineTo(baseX - PyT[sample], baseY - PxT[sample]);
        ed_LineTo(baseX - PyT2[sample], baseY - PxT2[sample]);
        editBufInvalidFlag[-3] = baseX + 10;
        edata[57] = baseY + 4;
        ed_LineTo(baseX - PyT[sample], baseY + PxT[sample]);
        ed_LineTo(baseX - PyT2[sample], baseY + PxT2[sample]);
        break;
    case 3:
        editBufInvalidFlag[-3] = baseX + 10;
        edata[57] = baseY + 3;
        ed_LineTo(baseX + PxD[sample], baseY - PyD[sample]);
        ed_LineTo(baseX + PxD2[sample], baseY - PyD2[sample]);
        editBufInvalidFlag[-3] = baseX + 3;
        edata[57] = baseY + 10;
        ed_LineTo(baseX - PyD[sample], baseY + PxD[sample]);
        ed_LineTo(baseX - PyD2[sample], baseY + PxD2[sample]);
        break;
    case 4:
        editBufInvalidFlag[-3] = baseX + 4;
        edata[57] = baseY + 10;
        ed_LineTo(baseX + PxT[sample], baseY - PyT[sample]);
        ed_LineTo(baseX + PxT2[sample], baseY - PyT2[sample]);
        editBufInvalidFlag[-3] = baseX - 4;
        edata[57] = baseY + 10;
        ed_LineTo(baseX - PxT[sample], baseY - PyT[sample]);
        ed_LineTo(baseX - PxT2[sample], baseY + PyT2[sample]);
        break;
    case 5:
        editBufInvalidFlag[-3] = baseX - 10;
        edata[57] = baseY + 3;
        ed_LineTo(baseX - PxD[sample], baseY - PyD[sample]);
        ed_LineTo(baseX - PxD2[sample], baseY - PyD2[sample]);
        editBufInvalidFlag[-3] = baseX - 3;
        edata[57] = baseY + 10;
        ed_LineTo(baseX + PyD[sample], baseY + PxD[sample]);
        ed_LineTo(baseX + PyD2[sample], baseY + PxD2[sample]);
        break;
    case 6:
        editBufInvalidFlag[-3] = baseX - 10;
        edata[57] = baseY - 4;
        ed_LineTo(baseX + PyT[sample], baseY - PxT[sample]);
        ed_LineTo(baseX + PyT2[sample], baseY - PxT2[sample]);
        editBufInvalidFlag[-3] = baseX - 10;
        edata[57] = baseY + 4;
        ed_LineTo(baseX + PyT[sample], baseY + PxT[sample]);
        ed_LineTo(baseX + PyT2[sample], baseY + PxT2[sample]);
        break;
    case 7:
        editBufInvalidFlag[-3] = baseX - 10;
        edata[57] = baseY - 3;
        ed_LineTo(baseX - PxD[sample], baseY + PyD[sample]);
        ed_LineTo(baseX - PxD2[sample], baseY + PyD2[sample]);
        editBufInvalidFlag[-3] = baseX - 3;
        edata[57] = baseY - 10;
        ed_LineTo(baseX + PyD[sample], baseY - PxD[sample]);
        ed_LineTo(baseX + PyD2[sample], baseY - PxD2[sample]);
        break;
    }
}
