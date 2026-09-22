/* GetMowDir: try each of 4 directions (3 down to 0), stepping (row,col)
 * by the private direction-delta bytes at match_position's segment
 * (+0x25d4 row delta, +0x25d8 column delta, indexed by direction) from
 * the caller's (row,col); an in-range (0<=row<=0xb, 0<=col<=0xf) tile
 * whose mow-bitmap bit is set (a private word-per-row array at
 * match_position-0x5f4a) is claimed (bit cleared) and that direction is
 * returned.  If no direction works: row>10 returns 0; else col>14
 * returns 1; else col<1 queues a "come mow" boy message (BoyMsgCnt =
 * MacTickCount()+300, BoyMessOn=1, BoyMsgOffset=6, BoyHere=4) and
 * returns 2; otherwise returns YardCycle&3.
 */

extern int far match_position[];
#define B9(off) (*(unsigned char far *)((char far *)match_position + (off)))
#define W9(off) (*(unsigned int far *)((char far *)match_position + (off)))

extern unsigned long far BoyMsgCnt;
extern int far BoyMessOn;
extern int near BoyHere;
extern int far BoyMsgOffset;
extern int far YardCycle;

extern unsigned long far MacTickCount(void);

int far GetMowDir(int row, int col)
{
    int dir;
    int newRow, newCol;
    int bit;
    int found;

    for (dir = 3; dir >= 0; dir--) {
        found = 0;
        newRow = row + (signed char)B9(0x25d4 + dir);
        newCol = col + (signed char)B9(0x25d8 + dir);
        if (newRow >= 0 && newCol >= 0 && newRow <= 0xb && newCol <= 0xf) {
            bit = 1 << newCol;
            if (W9(-0x5f4a + newRow * 2) & bit) {
                W9(-0x5f4a + newRow * 2) -= bit;
                found = 1;
            }
        }
        if (found)
            return dir;
    }

    if (row > 0xa)
        return 0;
    if (col > 0xe)
        return 1;
    if (col < 1) {
        BoyMsgCnt = MacTickCount() + 0x12cL;
        BoyMessOn = 1;
        BoyMsgOffset = 6;
        BoyHere = 4;
        return 2;
    }
    return YardCycle & 3;
}
