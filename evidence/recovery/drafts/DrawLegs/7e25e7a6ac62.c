/* Draw the sixteen-segment outline for the selected body orientation.
 * L/D tables provide signed per-phase offsets; the second pass uses phase
 * rotated by four steps.  The four current-point anchors are the editor
 * scratch words consumed by ed_LineTo. */
extern int far ConvColor(int color);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far ed_LineTo(int x, int y);
extern int far editBufInvalidFlag[];
extern int near edata[];
extern char far Lx[];
extern char far Ly[];
extern char far Dx[];
extern char far Dy[];
extern char far L1xA[];
extern char far L1xB[];
extern char far L1yA[];
extern char far L1yB[];
extern char far L2xA[];
extern char far L2xB[];
extern char far L2yA[];
extern char far L2yB[];
extern char far L3xA[];
extern char far L3xB[];
extern char far L3yA[];
extern char far L3yB[];
extern char far L4xA[];
extern char far L4xB[];
extern char far L4yA[];
extern char far L4yB[];
extern char far D1xA[];
extern char far D1xB[];
extern char far D1yA[];
extern char far D1yB[];
extern char far D2xA[];
extern char far D2xB[];
extern char far D2yA[];
extern char far D2yB[];
extern char far D3xA[];
extern char far D3xB[];
extern char far D3yA[];
extern char far D3yB[];
extern char far D4xA[];
extern char far D4xB[];
extern char far D4yA[];
extern char far D4yB[];

void far DrawLegs(int x, int y, int body, unsigned char phase)
{
    int far *penX;
    volatile int phaseIndex;

    phaseIndex = (unsigned char)(phase - 0xfc) & 7;
    GSetAttrib(ConvColor(15), 0, 0);

    switch (body) {
    case 0:
    {
        register int baseX = x;
        register int baseY = y;
        /* Orientation 0: use the L anchors. */
        penX = editBufInvalidFlag - 3;
        *penX = baseX + Lx[0];
        edata[57] = baseY + Ly[0];
        ed_LineTo(baseX + L1xA[phase], baseY + L1yA[phase]);
        ed_LineTo(baseX + L1xB[phase], baseY + L1yB[phase]);
        *penX = baseX + Lx[1];
        edata[57] = baseY + Ly[1];
        ed_LineTo(baseX + L2xA[phase], baseY + L2yA[phase]);
        ed_LineTo(baseX + L2xB[phase], baseY + L2yB[phase]);
        *penX = baseX + Lx[2];
        edata[57] = baseY + Ly[2];
        ed_LineTo(baseX + L3xA[phase], baseY + L3yA[phase]);
        ed_LineTo(baseX + L3xB[phase], baseY + L3yB[phase]);
        *penX = baseX + Lx[3];
        edata[57] = baseY + Ly[3];
        ed_LineTo(baseX + L4xA[phase], baseY + L4yA[phase]);
        ed_LineTo(baseX + L4xB[phase], baseY + L4yB[phase]);
        *penX = baseX + Lx[0];
        edata[57] = baseY + Ly[0];
        ed_LineTo(baseX - L1xA[phaseIndex], baseY + L1yA[phaseIndex]);
        ed_LineTo(baseX - L1xB[phaseIndex], baseY + L1yB[phaseIndex]);
        *penX = baseX + Lx[1];
        edata[57] = baseY + Ly[1];
        ed_LineTo(baseX - L2xA[phaseIndex], baseY + L2yA[phaseIndex]);
        ed_LineTo(baseX - L2xB[phaseIndex], baseY + L2yB[phaseIndex]);
        *penX = baseX + Lx[2];
        edata[57] = baseY + Ly[2];
        ed_LineTo(baseX - L3xA[phaseIndex], baseY + L3yA[phaseIndex]);
        ed_LineTo(baseX - L3xB[phaseIndex], baseY + L3yB[phaseIndex]);
        *penX = baseX + Lx[3];
        edata[57] = baseY + Ly[3];
        ed_LineTo(baseX - L4xA[phaseIndex], baseY + L4yA[phaseIndex]);
        ed_LineTo(baseX + L4yB[phaseIndex], baseY - L4xB[phaseIndex]);
        break;
    }
    case 1:
    {
        register int baseX = x;
        register int baseY = y;
        /* Orientation 1: use the D anchors. */
        penX = editBufInvalidFlag - 3;
        *penX = baseX + Dx[0];
        edata[57] = baseY + Dy[0];
        ed_LineTo(baseX + D1xA[phase], baseY + D1yA[phase]);
        ed_LineTo(baseX + D1xB[phase], baseY + D1yB[phase]);
        *penX = baseX + Dx[1];
        edata[57] = baseY + Dy[1];
        ed_LineTo(baseX + D2xA[phase], baseY + D2yA[phase]);
        ed_LineTo(baseX + D2xB[phase], baseY + D2yB[phase]);
        *penX = baseX + Dx[2];
        edata[57] = baseY + Dy[2];
        ed_LineTo(baseX + D3xA[phase], baseY + D3yA[phase]);
        ed_LineTo(baseX + D3xB[phase], baseY + D3yB[phase]);
        *penX = baseX + Dx[3];
        edata[57] = baseY + Dy[3];
        ed_LineTo(baseX + D4xA[phase], baseY + D4yA[phase]);
        ed_LineTo(baseX + D4xB[phase], baseY + D4yB[phase]);
        *penX = baseX + Dx[0];
        edata[57] = baseY + Dy[0];
        ed_LineTo(baseX - D1yA[phaseIndex], baseY - D1xA[phaseIndex]);
        ed_LineTo(baseX - D1yB[phaseIndex], baseY - D1xB[phaseIndex]);
        *penX = baseX + Dx[1];
        edata[57] = baseY + Dy[1];
        ed_LineTo(baseX - D2yA[phaseIndex], baseY - D2xA[phaseIndex]);
        ed_LineTo(baseX - D2yB[phaseIndex], baseY - D2xB[phaseIndex]);
        *penX = baseX + Dx[2];
        edata[57] = baseY + Dy[2];
        ed_LineTo(baseX - D3yA[phaseIndex], baseY - D3xA[phaseIndex]);
        ed_LineTo(baseX - D3yB[phaseIndex], baseY - D3xB[phaseIndex]);
        *penX = baseX + Dx[3];
        edata[57] = baseY + Dy[3];
        ed_LineTo(baseX - D4yA[phaseIndex], baseY - D4xA[phaseIndex]);
        ed_LineTo(baseX - D4xB[phaseIndex], baseY - D4yB[phaseIndex]);
        break;
    }
    case 2:
    {
        register int baseX = x;
        register int baseY = y;
        /* Orientation 2: use the L anchors. */
        penX = editBufInvalidFlag - 3;
        *penX = baseX - Ly[0];
        edata[57] = baseY + Lx[0];
        ed_LineTo(baseX - L1yA[phase], baseY + L1xA[phase]);
        ed_LineTo(baseX - L1yB[phase], baseY + L1xB[phase]);
        *penX = baseX - Ly[1];
        edata[57] = baseY + Lx[1];
        ed_LineTo(baseX - L2yA[phase], baseY + L2xA[phase]);
        ed_LineTo(baseX - L2yB[phase], baseY + L2xB[phase]);
        *penX = baseX - Ly[2];
        edata[57] = baseY + Lx[2];
        ed_LineTo(baseX - L3yA[phase], baseY + L3xA[phase]);
        ed_LineTo(baseX - L3yB[phase], baseY + L3xB[phase]);
        *penX = baseX - Ly[3];
        edata[57] = baseY + Lx[3];
        ed_LineTo(baseX - L4yA[phase], baseY + L4xA[phase]);
        ed_LineTo(baseX - L4yB[phase], baseY + L4xB[phase]);
        *penX = baseX - Ly[0];
        edata[57] = baseY + Lx[0];
        ed_LineTo(baseX - L1yA[phaseIndex], baseY - L1xA[phaseIndex]);
        ed_LineTo(baseX - L1yB[phaseIndex], baseY - L1xB[phaseIndex]);
        *penX = baseX - Ly[1];
        edata[57] = baseY + Lx[1];
        ed_LineTo(baseX - L2yA[phaseIndex], baseY - L2xA[phaseIndex]);
        ed_LineTo(baseX - L2yB[phaseIndex], baseY - L2xB[phaseIndex]);
        *penX = baseX - Ly[2];
        edata[57] = baseY + Lx[2];
        ed_LineTo(baseX - L3yA[phaseIndex], baseY - L3xA[phaseIndex]);
        ed_LineTo(baseX - L3yB[phaseIndex], baseY - L3xB[phaseIndex]);
        *penX = baseX - Ly[3];
        edata[57] = baseY + Lx[3];
        ed_LineTo(baseX - L4yA[phaseIndex], baseY - L4xA[phaseIndex]);
        ed_LineTo(baseX - L4xB[phaseIndex], baseY - L4yB[phaseIndex]);
        break;
    }
    case 3:
    {
        register int baseX = x;
        register int baseY = y;
        /* Orientation 3: use the D anchors. */
        penX = editBufInvalidFlag - 3;
        *penX = baseX + Dx[0];
        edata[57] = baseY - Dy[0];
        ed_LineTo(baseX + D1xA[phase], baseY - D1yA[phase]);
        ed_LineTo(baseX + D1xB[phase], baseY - D1yB[phase]);
        *penX = baseX + Dx[1];
        edata[57] = baseY - Dy[1];
        ed_LineTo(baseX + D2xA[phase], baseY - D2yA[phase]);
        ed_LineTo(baseX + D2xB[phase], baseY - D2yB[phase]);
        *penX = baseX + Dx[2];
        edata[57] = baseY - Dy[2];
        ed_LineTo(baseX + D3xA[phase], baseY - D3yA[phase]);
        ed_LineTo(baseX + D3xB[phase], baseY - D3yB[phase]);
        *penX = baseX + Dx[3];
        edata[57] = baseY - Dy[3];
        ed_LineTo(baseX + D4xA[phase], baseY - D4yA[phase]);
        ed_LineTo(baseX + D4xB[phase], baseY - D4yB[phase]);
        *penX = baseX + Dx[0];
        edata[57] = baseY - Dy[0];
        ed_LineTo(baseX - D1yA[phaseIndex], baseY + D1xA[phaseIndex]);
        ed_LineTo(baseX - D1yB[phaseIndex], baseY + D1xB[phaseIndex]);
        *penX = baseX + Dx[1];
        edata[57] = baseY - Dy[1];
        ed_LineTo(baseX - D2yA[phaseIndex], baseY + D2xA[phaseIndex]);
        ed_LineTo(baseX - D2yB[phaseIndex], baseY + D2xB[phaseIndex]);
        *penX = baseX + Dx[2];
        edata[57] = baseY - Dy[2];
        ed_LineTo(baseX - D3yA[phaseIndex], baseY + D3xA[phaseIndex]);
        ed_LineTo(baseX - D3yB[phaseIndex], baseY + D3xB[phaseIndex]);
        *penX = baseX + Dx[3];
        edata[57] = baseY - Dy[3];
        ed_LineTo(baseX - D4yA[phaseIndex], baseY + D4xA[phaseIndex]);
        ed_LineTo(baseX + D4xB[phaseIndex], baseY - D4yB[phaseIndex]);
        break;
    }
    case 4:
    {
        register int baseX = x;
        register int baseY = y;
        /* Orientation 4: use the L anchors. */
        penX = editBufInvalidFlag - 3;
        *penX = baseX - Lx[0];
        edata[57] = baseY - Ly[0];
        ed_LineTo(baseX - L1xA[phase], baseY - L1yA[phase]);
        ed_LineTo(baseX - L1xB[phase], baseY - L1yB[phase]);
        *penX = baseX - Lx[1];
        edata[57] = baseY - Ly[1];
        ed_LineTo(baseX - L2xA[phase], baseY - L2yA[phase]);
        ed_LineTo(baseX - L2xB[phase], baseY - L2yB[phase]);
        *penX = baseX - Lx[2];
        edata[57] = baseY - Ly[2];
        ed_LineTo(baseX - L3xA[phase], baseY - L3yA[phase]);
        ed_LineTo(baseX - L3xB[phase], baseY - L3yB[phase]);
        *penX = baseX - Lx[3];
        edata[57] = baseY - Ly[3];
        ed_LineTo(baseX - L4xA[phase], baseY - L4yA[phase]);
        ed_LineTo(baseX - L4xB[phase], baseY - L4yB[phase]);
        *penX = baseX - Lx[0];
        edata[57] = baseY - Ly[0];
        ed_LineTo(baseX + L1xA[phaseIndex], baseY - L1yA[phaseIndex]);
        ed_LineTo(baseX + L1xB[phaseIndex], baseY - L1yB[phaseIndex]);
        *penX = baseX - Lx[1];
        edata[57] = baseY - Ly[1];
        ed_LineTo(baseX + L2xA[phaseIndex], baseY - L2yA[phaseIndex]);
        ed_LineTo(baseX + L2xB[phaseIndex], baseY - L2yB[phaseIndex]);
        *penX = baseX - Lx[2];
        edata[57] = baseY - Ly[2];
        ed_LineTo(baseX + L3xA[phaseIndex], baseY - L3yA[phaseIndex]);
        ed_LineTo(baseX + L3xB[phaseIndex], baseY - L3yB[phaseIndex]);
        *penX = baseX - Lx[3];
        edata[57] = baseY - Ly[3];
        ed_LineTo(baseX + L4xA[phaseIndex], baseY - L4yA[phaseIndex]);
        ed_LineTo(baseX - L4yB[phaseIndex], baseY + L4xB[phaseIndex]);
        break;
    }
    case 5:
    {
        register int baseX = x;
        register int baseY = y;
        /* Orientation 5: use the D anchors. */
        penX = editBufInvalidFlag - 3;
        *penX = baseX - Dx[0];
        edata[57] = baseY - Dy[0];
        ed_LineTo(baseX - D1xA[phase], baseY - D1yA[phase]);
        ed_LineTo(baseX - D1xB[phase], baseY - D1yB[phase]);
        *penX = baseX - Dx[1];
        edata[57] = baseY - Dy[1];
        ed_LineTo(baseX - D2xA[phase], baseY - D2yA[phase]);
        ed_LineTo(baseX - D2xB[phase], baseY - D2yB[phase]);
        *penX = baseX - Dx[2];
        edata[57] = baseY - Dy[2];
        ed_LineTo(baseX - D3xA[phase], baseY - D3yA[phase]);
        ed_LineTo(baseX - D3xB[phase], baseY - D3yB[phase]);
        *penX = baseX - Dx[3];
        edata[57] = baseY - Dy[3];
        ed_LineTo(baseX - D4xA[phase], baseY - D4yA[phase]);
        ed_LineTo(baseX - D4xB[phase], baseY - D4yB[phase]);
        *penX = baseX - Dx[0];
        edata[57] = baseY - Dy[0];
        ed_LineTo(baseX + D1yA[phaseIndex], baseY + D1xA[phaseIndex]);
        ed_LineTo(baseX + D1yB[phaseIndex], baseY + D1xB[phaseIndex]);
        *penX = baseX - Dx[1];
        edata[57] = baseY - Dy[1];
        ed_LineTo(baseX + D2yA[phaseIndex], baseY + D2xA[phaseIndex]);
        ed_LineTo(baseX + D2yB[phaseIndex], baseY + D2xB[phaseIndex]);
        *penX = baseX - Dx[2];
        edata[57] = baseY - Dy[2];
        ed_LineTo(baseX + D3yA[phaseIndex], baseY + D3xA[phaseIndex]);
        ed_LineTo(baseX + D3yB[phaseIndex], baseY + D3xB[phaseIndex]);
        *penX = baseX - Dx[3];
        edata[57] = baseY - Dy[3];
        ed_LineTo(baseX + D4yA[phaseIndex], baseY + D4xA[phaseIndex]);
        ed_LineTo(baseX + D4xB[phaseIndex], baseY + D4yB[phaseIndex]);
        break;
    }
    case 6:
    {
        register int baseX = x;
        register int baseY = y;
        /* Orientation 6: use the L anchors. */
        penX = editBufInvalidFlag - 3;
        *penX = baseX + Ly[0];
        edata[57] = baseY - Lx[0];
        ed_LineTo(baseX + L1yA[phase], baseY - L1xA[phase]);
        ed_LineTo(baseX + L1yB[phase], baseY - L1xB[phase]);
        *penX = baseX + Ly[1];
        edata[57] = baseY - Lx[1];
        ed_LineTo(baseX + L2yA[phase], baseY - L2xA[phase]);
        ed_LineTo(baseX + L2yB[phase], baseY - L2xB[phase]);
        *penX = baseX + Ly[2];
        edata[57] = baseY - Lx[2];
        ed_LineTo(baseX + L3yA[phase], baseY - L3xA[phase]);
        ed_LineTo(baseX + L3yB[phase], baseY - L3xB[phase]);
        *penX = baseX + Ly[3];
        edata[57] = baseY - Lx[3];
        ed_LineTo(baseX + L4yA[phase], baseY - L4xA[phase]);
        ed_LineTo(baseX + L4yB[phase], baseY - L4xB[phase]);
        *penX = baseX + Ly[0];
        edata[57] = baseY - Lx[0];
        ed_LineTo(baseX + L1yA[phaseIndex], baseY + L1xA[phaseIndex]);
        ed_LineTo(baseX + L1yB[phaseIndex], baseY + L1xB[phaseIndex]);
        *penX = baseX + Ly[1];
        edata[57] = baseY - Lx[1];
        ed_LineTo(baseX + L2yA[phaseIndex], baseY + L2xA[phaseIndex]);
        ed_LineTo(baseX + L2yB[phaseIndex], baseY + L2xB[phaseIndex]);
        *penX = baseX + Ly[2];
        edata[57] = baseY - Lx[2];
        ed_LineTo(baseX + L3yA[phaseIndex], baseY + L3xA[phaseIndex]);
        ed_LineTo(baseX + L3yB[phaseIndex], baseY + L3xB[phaseIndex]);
        *penX = baseX + Ly[3];
        edata[57] = baseY - Lx[3];
        ed_LineTo(baseX + L4yA[phaseIndex], baseY + L4xA[phaseIndex]);
        ed_LineTo(baseX + L4xB[phaseIndex], baseY + L4yB[phaseIndex]);
        break;
    }
    case 7:
    {
        register int baseX = x;
        register int baseY = y;
        /* Orientation 7: use the D anchors. */
        penX = editBufInvalidFlag - 3;
        *penX = baseX - Dx[0];
        edata[57] = baseY + Dy[0];
        ed_LineTo(baseX - D1xA[phase], baseY + D1yA[phase]);
        ed_LineTo(baseX - D1xB[phase], baseY + D1yB[phase]);
        *penX = baseX - Dx[1];
        edata[57] = baseY + Dy[1];
        ed_LineTo(baseX - D2xA[phase], baseY + D2yA[phase]);
        ed_LineTo(baseX - D2xB[phase], baseY + D2yB[phase]);
        *penX = baseX - Dx[2];
        edata[57] = baseY + Dy[2];
        ed_LineTo(baseX - D3xA[phase], baseY + D3yA[phase]);
        ed_LineTo(baseX - D3xB[phase], baseY + D3yB[phase]);
        *penX = baseX - Dx[3];
        edata[57] = baseY + Dy[3];
        ed_LineTo(baseX - D4xA[phase], baseY + D4yA[phase]);
        ed_LineTo(baseX - D4xB[phase], baseY + D4yB[phase]);
        *penX = baseX - Dx[0];
        edata[57] = baseY + Dy[0];
        ed_LineTo(baseX + D1yA[phaseIndex], baseY - D1xA[phaseIndex]);
        ed_LineTo(baseX + D1yB[phaseIndex], baseY - D1xB[phaseIndex]);
        *penX = baseX - Dx[1];
        edata[57] = baseY + Dy[1];
        ed_LineTo(baseX + D2yA[phaseIndex], baseY - D2xA[phaseIndex]);
        ed_LineTo(baseX + D2yB[phaseIndex], baseY - D2xB[phaseIndex]);
        *penX = baseX - Dx[2];
        edata[57] = baseY + Dy[2];
        ed_LineTo(baseX + D3yA[phaseIndex], baseY - D3xA[phaseIndex]);
        ed_LineTo(baseX + D3yB[phaseIndex], baseY - D3xB[phaseIndex]);
        *penX = baseX - Dx[3];
        edata[57] = baseY + Dy[3];
        ed_LineTo(baseX + D4yA[phaseIndex], baseY - D4xA[phaseIndex]);
        ed_LineTo(baseX - D4xB[phaseIndex], baseY + D4yB[phaseIndex]);
        break;
    }
    }
}
