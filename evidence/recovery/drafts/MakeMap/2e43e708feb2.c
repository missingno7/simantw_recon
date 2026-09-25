extern void far MakeYardPatch(int value);
extern void far MakeHousePatch(void);

void MakeMap(int row, int column)
{
    int value;

    value = (row << 4) + column;
    if (value > 0x25)
        MakeHousePatch();
    else
        MakeYardPatch(value);
}
