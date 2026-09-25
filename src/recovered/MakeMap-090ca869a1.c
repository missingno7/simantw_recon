/* Cell indices above 37 generate the yard patch; smaller indices generate the house patch. */
extern void far MakeYardPatch(void);
extern void far MakeHousePatch(int value);

void MakeMap(int row, int column)
{
    int value;

    value = (row << 4) + column;
    if (value > 0x25)
        MakeYardPatch();
    else
        MakeHousePatch(value);
}
