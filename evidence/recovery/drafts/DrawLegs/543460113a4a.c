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
    int limb;
    int joint;
    int px;
    int py;
    int side;
    int sign;

    phase = (phase - 0xfc) & 7;
    GSetAttrib(ConvColor(15), 0, 0);

    for (limb = 0; limb < 8; ++limb) {
        side = (limb < 4) ? -1 : 1;
        sign = ((limb + phase) & 1) ? -1 : 1;
        if (group > 7 && ((limb + group) & 1) != 0)
            continue;

        px = x + side * (2 + (limb & 1));
        py = y + ((limb < 4) ? -1 : 1);
        ed_LineTo(px, py);

        for (joint = 0; joint < 4; ++joint) {
            px += side * (3 + group + joint);
            py += sign * (2 + ((phase + joint) & 3));
            ed_LineTo(px, py);
        }
    }
}
