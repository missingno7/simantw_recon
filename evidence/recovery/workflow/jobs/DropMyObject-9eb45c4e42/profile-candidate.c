extern unsigned int near MeType;
extern void far DropMyEgg(int, int, int, int, int);
extern void far DropMyFood(int, int, int, int, int);
extern void far DropMyRock(int, int, int, int, int);

void DropMyObject(int first, int second, int third, int fourth, int fifth)
{
    if (MeType == 0x48)
        goto rock;
    if (MeType > 0x48)
        return;
    if (MeType - 8 == 0)
        goto egg;
    if (MeType - 8 - 0x10 == 0)
        goto food;
    if (MeType - 8 - 0x10 - 0x10 == 0)
        goto rock;
    if (MeType - 8 - 0x10 - 0x10 - 0x10 == 0)
        goto food;
    return;

egg:
    DropMyEgg(first, second, third, fourth, fifth);
    return;

food:
    DropMyFood(first, second, third, fourth, fifth);
    return;

rock:
    DropMyRock(first, second, third, fourth, fifth);
}
