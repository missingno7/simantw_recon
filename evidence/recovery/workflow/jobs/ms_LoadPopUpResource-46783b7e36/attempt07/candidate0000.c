extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far *mem_Lock(unsigned int handle);
extern void far *mem_malloc(unsigned int size, char far *name);
extern int far mem_Unlock(unsigned int handle);
extern void far WinPrintf(char far *format, ...);

char far * far ms_LoadPopUpResource(int resourceID, int far *count)
{
    unsigned int handle;
    unsigned char far *input;
    unsigned char far *scan;
    char far *allocation;
    char far * near *table;
    char far *output;
    int records;
    int total;
    int i;
    int length;
    int j;

    handle = db_LoadObject(resourceID, 6, 1);
    if (!handle) {
        WinPrintf("\nCouldn't load menu %d", resourceID);
        *count = 0;
        return (char far *)0;
    }
    input = (unsigned char far *)mem_Lock(handle);
    input++;
    records = *input++;
    scan = input;
    total = 0;
    for (i = 0; i < records; i++) {
        total += *scan + 2;
        scan += *scan + 1;
    }
    allocation = (char far *)mem_malloc(total + (records + 1) * 4, "strptrs");
    table = (char far * near *)allocation;
    output = allocation + (records + 1) * 4;
    for (i = 0; i < records; i++) {
        length = *input++;
        if (!length)
            break;
        *table++ = output;
        *output++ = ' ';
        for (j = 0; j < length; j++)
            output[j] = input[j];
        output += length;
        input += length;
        *output++ = 0;
        input++;
    }
    *table = (char far *)0;
    mem_Unlock(handle);
    *count = i;
    return allocation;
}
