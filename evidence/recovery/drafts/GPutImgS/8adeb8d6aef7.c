/* GPutImgS: draw a small monochrome image through DoMonoBitmap. */
extern void far DoMonoBitmap(int x, int y, int arg3, int arg4, int arg5, int arg6, int arg7);

void GPutImgS(int first, int second, int third, int fourth,
              int fifth, int sixth, int seventh)
{
    volatile struct Local {
        int x;
        int padding;
    } local;
    local.x = first;
    DoMonoBitmap(local.x, second, fifth, sixth, third, fourth, seventh);
}
