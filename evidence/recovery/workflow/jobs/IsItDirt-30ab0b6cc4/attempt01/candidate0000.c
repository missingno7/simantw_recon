/*
 * IsItDirt recognizes the inclusive character-code interval used for dirt
 * tiles.  The original compares the complete 16-bit argument as a signed
 * value, so values below space and above period are rejected.
 */
int IsItDirt(int value)
{
    if (value < 0x20 || value > 0x2e) return 0;
    return 1;
}
