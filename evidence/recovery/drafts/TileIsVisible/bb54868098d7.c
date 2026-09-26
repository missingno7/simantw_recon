/* The left and top values are adjacent PACK words. */
extern volatile int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far match_position[];

int TileIsVisible(int plane, int x, int y)
{
    int visible;
    visible = plane == MapPlane &&
        match_position[0x3e97] <= x &&
        match_position[0x3e97] + editWidth > x &&
        match_position[0x3e98] <= y &&
        match_position[0x3e98] + editHeight > y;
    return visible;
}
