extern unsigned char far editBufInvalidFlag[];

void ClearLastFileName(void)
{
    editBufInvalidFlag[1834] = 0;
}
