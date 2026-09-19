/* Candidate reconstruction using the named current-plane global. */
#define MePlane (*(int near *)0xCE80)

int IsSamePlane(int plane)
{
    int test;
    if (plane == 0) test = 1;
    else test = plane;
    return test == MePlane;
}
