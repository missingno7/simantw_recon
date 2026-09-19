/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern int near MePlane;

int IsSamePlane(volatile int plane)
{
    if (plane == 0) plane = 1;
    if (plane == MePlane) return 1;
    return 0;
}
