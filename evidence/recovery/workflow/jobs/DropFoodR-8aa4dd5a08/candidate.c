extern unsigned char near MapR[];
extern int far FoodR[];
extern int far Tindex[];
extern unsigned char far Dx8[];

int DropFoodR(int row, int column)
{
    unsigned char *cell;
    unsigned char far *ant;
    int changed;

    changed = 0;
    cell = MapR + (row << 6) + column;
    if (*cell < 0x10) {
        *cell = 0x10;
        changed = 1;
    } else if (*cell < 0x13) {
        ++*cell;
        changed = 1;
    }
    ++FoodR[0x396f];
    ant = Dx8 + Tindex[0x4db5] + 0x46e6;
    if (*ant & 8)
        *ant -= 8;
    return changed;
}
