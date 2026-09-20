extern int far Scycle[];
extern int far pascal ModifyMenu(unsigned int menu, unsigned int item,
                                 unsigned int flags, unsigned int newItem,
                                 char far *text);

void SetMenuOptionText(int item, char far *text)
{
    ModifyMenu(Scycle[-23 + ((item & 0xf0) >> 4)],
               item | 0xfd00,
               0,
               item | 0xfd00,
               text);
}
