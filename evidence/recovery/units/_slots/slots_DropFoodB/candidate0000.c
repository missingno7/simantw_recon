/* Use the admitted BList field view for the byte located at BlistX + Tindex. */
struct BListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct BListPlanes far BlistX;
extern unsigned char near MapB[];
extern int far FoodB;
extern int far Tindex;

int far DropFoodB(int x, int y)
{
    int level;
    int result;

    result = 0;
    level = MapB[(x << 6) + y];
    if (level < 16) {
        MapB[(x << 6) + y] = 16;
        result = 1;
    } else if (level < 19) {
        MapB[(x << 6) + y]++;
        result = 1;
    }
    ++FoodB;
    if (BlistX.t[Tindex] & 8)
        BlistX.t[Tindex] -= 8;
    return result;
}
