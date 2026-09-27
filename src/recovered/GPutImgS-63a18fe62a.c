/* GPutImgS: adapt seven drawing arguments to DoMonoBitmap.  The two-word local holds the first coordinate; x is volatile because the target writes it at BP-4 and pushes that home, while y remains a register value through the other argument pushes. */
extern void far DoMonoBitmap(int x, int y, int arg3, int arg4, int arg5, int arg6, int arg7);
void GPutImgS(int first, int second, int third, int fourth, int fifth, int sixth, int seventh)
{
    struct Local { volatile int x; int y; } local;
    local.x = first;
    local.y = second;
    DoMonoBitmap(local.x, local.y, fifth, sixth, third, fourth, seventh);
}