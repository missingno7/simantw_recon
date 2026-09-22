/*
 * DropMyObject dispatches to the drop routine for the carried object type.
 * The target's compare chain (a direct check against the largest case
 * value 0x48, a bail-out above it, then a sequential -8/-0x10/-0x10/-0x10
 * subtract-and-test cascade for 8, 0x18, 0x28, 0x38) and its block order
 * (egg, then food, then rock) are the standard MSC7 codegen for a sparse
 * switch written with fallthrough case groups, in source order.
 */
extern int near MeType;
extern void far DropMyEgg(int, int, int, int, int);
extern void far DropMyFood(int, int, int, int, int);
extern void far DropMyRock(int, int, int, int, int);

void far DropMyObject(int first, int second, int third, int fourth, int fifth)
{
    switch (MeType) {
    case 8:
        DropMyEgg(first, second, third, fourth, fifth);
        break;
    case 0x18:
    case 0x38:
        DropMyFood(first, second, third, fourth, fifth);
        break;
    case 0x28:
    case 0x48:
        DropMyRock(first, second, third, fourth, fifth);
        break;
    }
}
