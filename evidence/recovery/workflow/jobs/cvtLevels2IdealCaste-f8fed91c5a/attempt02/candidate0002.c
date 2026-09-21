/*
 * cvtLevels2IdealCaste: turn the far casteLevels shares (0..65535) into
 * ideal caste counts: the first two results are 100 times levels 1 and 2,
 * the last two 50 times level 0, each rounded (plus 0x3fff) and divided
 * by 65535 in unsigned 32-bit arithmetic, stored through the far result
 * pointer.
 */
extern unsigned int far casteLevels[];
#define HUNDRED 100UL
#define FIFTY 50UL

void far cvtLevels2IdealCaste(int far *ideal)
{
    ideal[0] = (HUNDRED * casteLevels[1] + 0x3fff) / 0xffff;
    ideal[1] = (HUNDRED * casteLevels[2] + 0x3fff) / 0xffff;
    ideal[2] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
    ideal[3] = (FIFTY * casteLevels[0] + 0x3fffUL) / 0xffffUL;
}
