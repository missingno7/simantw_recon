/*
 * Hypothesis: draw an eight-limb outline from the supplied anchor point.
 * The fourth argument selects one of eight gait phases, while the third
 * argument selects the body group whose leg lengths and bends are used.
 */
extern int far ConvColor(int color);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void near ed_LineTo(int x, int y);

void far DrawLegs(int x, int y, int group, unsigned char phase)
{
    int phaseIndex;
    int limb;
    int joint;
    int side;
    int px;

    phaseIndex = ((unsigned char)phase - 0xfc) & 7;
    GSetAttrib(ConvColor(15), 0, 0);

    switch (group) {
    case 0:
        for (limb = 0; limb < 8; ++limb) {
            side = (limb < 4) ? -1 : 1;
            px = x + side * (2 + (limb & 1));
            ed_LineTo(px, y + ((limb < 4) ? -1 : 1));
            for (joint = 0; joint < 8; ++joint) {
                px += side * (3 + joint);
                ed_LineTo(px, y + ((phaseIndex + joint) & 7) - 3);
            }
        }
        break;
    case 1:
        for (limb = 0; limb < 8; ++limb) {
            side = (limb < 4) ? -1 : 1;
            px = x + side * (3 + (limb & 1));
            ed_LineTo(px, y + ((limb < 4) ? -2 : 2));
            for (joint = 0; joint < 9; ++joint) {
                px += side * (4 + joint);
                ed_LineTo(px, y + ((phaseIndex + joint + 1) & 7) - 3);
            }
        }
        break;
    case 2:
        for (limb = 0; limb < 8; ++limb) {
            side = (limb < 4) ? -1 : 1;
            px = x + side * (4 + (limb & 1));
            ed_LineTo(px, y + ((limb < 4) ? -2 : 2));
            for (joint = 0; joint < 10; ++joint) {
                px += side * (2 + joint);
                ed_LineTo(px, y + ((phaseIndex + joint + 2) & 7) - 3);
            }
        }
        break;
    case 3:
        for (limb = 0; limb < 8; ++limb) {
            side = (limb < 4) ? -1 : 1;
            px = x + side * (2 + (limb & 1));
            ed_LineTo(px, y + ((limb < 4) ? -3 : 3));
            for (joint = 0; joint < 11; ++joint) {
                px += side * (3 + (joint & 3));
                ed_LineTo(px, y + ((phaseIndex + joint + 3) & 7) - 3);
            }
        }
        break;
    case 4:
        for (limb = 0; limb < 8; ++limb) {
            side = (limb < 4) ? -1 : 1;
            px = x + side * (5 + (limb & 1));
            ed_LineTo(px, y + ((limb < 4) ? -3 : 3));
            for (joint = 0; joint < 12; ++joint) {
                px += side * (2 + (joint & 3));
                ed_LineTo(px, y + ((phaseIndex + joint + 4) & 7) - 3);
            }
        }
        break;
    case 5:
        for (limb = 0; limb < 8; ++limb) {
            side = (limb < 4) ? -1 : 1;
            px = x + side * (3 + (limb & 1));
            ed_LineTo(px, y + ((limb < 4) ? -4 : 4));
            for (joint = 0; joint < 13; ++joint) {
                px += side * (4 + (joint & 1));
                ed_LineTo(px, y + ((phaseIndex + joint + 5) & 7) - 3);
            }
        }
        break;
    case 6:
        for (limb = 0; limb < 8; ++limb) {
            side = (limb < 4) ? -1 : 1;
            px = x + side * (4 + (limb & 1));
            ed_LineTo(px, y + ((limb < 4) ? -4 : 4));
            for (joint = 0; joint < 14; ++joint) {
                px += side * (2 + (joint & 3));
                ed_LineTo(px, y + ((phaseIndex + joint + 6) & 7) - 3);
            }
        }
        break;
    case 7:
        for (limb = 0; limb < 8; ++limb) {
            side = (limb < 4) ? -1 : 1;
            px = x + side * (5 + (limb & 1));
            ed_LineTo(px, y + ((limb < 4) ? -5 : 5));
            for (joint = 0; joint < 15; ++joint) {
                px += side * (3 + (joint & 3));
                ed_LineTo(px, y + ((phaseIndex + joint + 7) & 7) - 3);
            }
        }
        break;
    }
}
