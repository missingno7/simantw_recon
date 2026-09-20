extern int near MePlane;

int IsSamePlane(int plane)
{
    return (plane == 0 ? 1 : plane) == MePlane;
}
