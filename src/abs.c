/* Reconstructed from SIMANT_MODULE:_ABS. Filename is modern, not recovered.
 * Microsoft 16-bit int behavior (including INT_MIN wrap) is intentional.
 */
int far ABS(int value)
{
    if (value < 0)
        return -value;
    return value;
}
