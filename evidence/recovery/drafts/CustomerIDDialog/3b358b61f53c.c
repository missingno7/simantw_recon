/* Show the customer ID dialog with its mixed resource and literal strings. */
extern unsigned char far Dx8[];
extern unsigned int far custIDStrHandle;

extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_PurgeObject(int object, int kind);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern char far * far DecodeString(char far *source);
extern void far win_FlushEvents(void);
extern void far PictureDialog(char far * far *strings, int count, int picture, int force);

void far CustomerIDDialog(void)
{
    unsigned int object83;
    unsigned int object84;
    char far *strings[6];

    object83 = db_LoadObject(0x83, 0x0a, 0);
    object84 = db_LoadObject(0x84, 0x0a, 0);

    strings[0] = (char far *)mem_Lock(object83);
    strings[1] = DecodeString((char far *)&Dx8[0x8b3e]);
    strings[2] = " ";
    strings[3] = (char far *)mem_Lock(object84);
    strings[4] = (char far *)mem_Lock(custIDStrHandle);
    strings[5] = " ";

    win_FlushEvents();
    PictureDialog(strings, 6, 0, 1);

    mem_Unlock(object83);
    mem_Unlock(object84);
    mem_Unlock(custIDStrHandle);
    db_PurgeObject(0x83, 0x0a);
    db_PurgeObject(0x84, 0x0a);
}
