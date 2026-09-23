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
    char far * far *table;
    char far *output;
    int records;
    int total;
    int i;
    int length;

    handle = db_LoadObject(resourceID, 6, 1);
    if (handle == 0) {
        WinPrintf("\nCouldn't load menu %d", resourceID);
        *count = 0;
        return (char far *)0;
    }

    input = (unsigned char far *)mem_Lock(handle);
    records = input[1];
    scan = input + 2;
    total = 0;
    for (i = 0; i < records; ++i) {
        length = *scan;
        total += length + 2;
        scan += length + 1;
    }

    allocation = (char far *)mem_malloc((records + 1) * 4 + total, "strptrs");
    table = (char far * far *)allocation;
    output = allocation + (records + 1) * 4;
    for (i = 0; i < records; ++i) {
        length = *input++;
        if (length == 0)
            break;
        *table++ = output;
        *output++ = ' ';
        while (length--)
            *output++ = *input++;
        *output++ = '\0';
        input++;
    }
    *table = (char far *)0;
    mem_Unlock(handle);
    *count = i;
    return allocation;
}
