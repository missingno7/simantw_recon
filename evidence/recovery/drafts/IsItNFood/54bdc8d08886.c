/*
 * IsItNFood recognizes the inclusive four-value tile-code interval used for
 * food.  The signed word comparisons in the target reject values below 0x10
 * and above 0x13, returning a 16-bit boolean result.
 */
int IsItNFood(int value)
{
    if (value < 0x10 || value > 0x13) return 0;
    return 1;
}
