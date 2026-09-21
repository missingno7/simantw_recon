/*
 * Mini_MakeTable: build the mini-map colour table for the current display
 * type.  displayType is switched as a signed byte (cbw): type 9 is the
 * monochrome path, which caches the far PACK word multiplier (segment-9
 * selector slot 0xc228) and calls WindowsMono_MakeTable2x2b when the
 * multiplier is 0x40, otherwise WindowsMono_MakeTable2x2a, passing the
 * four table arguments, the multiplier and the fifth argument; type 10 is
 * the colour path calling Windows_MakeTable1x1 with the four arguments and
 * the multiplier.  Other display types do nothing.  The callees are far
 * entries in the graphics code group.
 */
extern char near displayType;
extern int far multiplier;
extern void far WindowsMono_MakeTable2x2b(int a, int b, int c, int d,
                                          int scale, int e);
extern void far WindowsMono_MakeTable2x2a(int a, int b, int c, int d,
                                          int scale, int e);
extern void far Windows_MakeTable1x1(int a, int b, int c, int d, int scale);

void far Mini_MakeTable(int a, int b, int c, int d, int e)
{
    int scale;

    switch (displayType) {
    case 9:
        scale = multiplier;
        if (scale == 0x40)
            WindowsMono_MakeTable2x2b(a, b, c, d, scale, e);
        else
            WindowsMono_MakeTable2x2a(a, b, c, d, scale, e);
        break;
    case 10:
        Windows_MakeTable1x1(a, b, c, d, multiplier);
        break;
    }
}
