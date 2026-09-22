extern int far editBufInvalidFlag[];
extern int near edata[];

void ed_MoveTo(int x, int y)
{
    editBufInvalidFlag[-3] = x;
    edata[57] = y;
}
