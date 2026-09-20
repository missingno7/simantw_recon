extern int far Scycle[];
extern int far pascal CheckMenuItem(unsigned int menu, unsigned int item,
                                    unsigned int flags);

void SetMenuOptionState(int item, int state)
{
    CheckMenuItem(Scycle[-23 + ((item & 0xf0) >> 4)],
                  item | 0xfd00,
                  state == 1 ? 8 : 0);
}
