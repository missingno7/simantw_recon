/* Preserve the target's source-level choice before the current-plane test. */
extern int near MePlane;

int IsSamePlane(int plane)
{
    int test;
    if (plane == 0)
        test = 1;
    else
        test = plane;
    return test == MePlane;
}
