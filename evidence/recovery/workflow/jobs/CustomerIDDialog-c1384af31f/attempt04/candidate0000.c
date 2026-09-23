/* Show the customer ID dialog with its mixed resource and literal strings. */
extern unsigned char far Dx8[];
extern unsigned int far custIDStrHandle;

extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_PurgeObject(int object, int kind);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern char far * near DecodeString(char far *source);
extern void far win_FlushEvents(void);
extern void far PictureDialog(char far * far *strings, int count, int picture, int force);

struct StringFrame {
    char far *string0; char far *string1; char far *string2;
    char far *string3; char far *string4; char far *string5;
    unsigned char tail[120];
};

void far CustomerIDDialog(void)
{
    unsigned int object83;
    unsigned int object84;
    struct StringFrame frame;

    object83 = db_LoadObject(0x83, 0x0a, 0);
    object84 = db_LoadObject(0x84, 0x0a, 0);

    frame.string0 = (char far *)mem_Lock(object83);
    frame.string1 = DecodeString((char far *)&Dx8[0x8b3e]);
    frame.string2 = " ";
    frame.string3 = (char far *)mem_Lock(object84);
    frame.string4 = (char far *)mem_Lock(custIDStrHandle);
    frame.string5 = " ";

    win_FlushEvents();
    PictureDialog(&frame.string0, 6, 0, 1);

    mem_Unlock(object83);
    mem_Unlock(object84);
    mem_Unlock(custIDStrHandle);
    db_PurgeObject(0x83, 0x0a);
    db_PurgeObject(0x84, 0x0a);
}
