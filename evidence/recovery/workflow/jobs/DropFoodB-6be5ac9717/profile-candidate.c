extern unsigned char near MapB[];
extern int far FoodB[];
extern int far Tindex[];
extern unsigned char far Dx8[];

int DropFoodB(int row, int column)
{
    unsigned char *cell;
    unsigned char far *ant;
    int changed;

    changed = 0;
    cell = MapB + (row << 6) + column;
    if (*cell < 0x10) {
        *cell = 0x10;
        changed = 1;
    } else if (*cell < 0x13) {
        ++*cell;
        changed = 1;
    }
    ++FoodB[0x4f52];
    ant = Dx8 + Tindex[0x4db5] + 0x3d18;
    if (*ant & 8)
        *ant -= 8;
    return changed;
}
