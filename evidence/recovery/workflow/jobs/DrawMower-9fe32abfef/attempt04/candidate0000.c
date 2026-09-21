/*
 * DrawMower: keep the yard's lawnmower animation object synced to the
 * boy's walk cycle.  Only while BoyHere is 3 or 4 (mowing) does the
 * mower move: if the game is paused it snaps straight to state 1;
 * otherwise the mower sound plays once and BoyFrame selects state 1
 * (frames 103-105, mower ahead-right of the boy) or state 2 (frames
 * 109-111, ahead-left) -- any other frame instead removes the shown
 * mower object (tagged "mower") and returns.  BoyHere not 3/4 leaves
 * state 0, the mower's fixed parked spot (0x62,0xb5); states 1/2 place
 * it at BoyX+19,BoyY+15 or BoyX-15,BoyY+15.  The object (animation
 * frame set 0x2260+state) is created the first time, repositioned
 * after.
 */
extern int near BoyHere;
extern int near BoyFrame;
extern int near BoyX;
extern int near BoyY;
extern int near yardAnimHandle;
extern int far GamePaused;
static int near mowerObject = -1;

extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far hanim_RemoveAnimObject(int animation, int object, char far *name);
extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);

void far DrawMower(void)
{
    int state;
    int bx, dx;

    state = 0;
    if (BoyHere == 3 || BoyHere == 4) {
        if (GamePaused != 0) {
            state = 1;
        } else {
            myBeginSound(0x40, 0, 0x24);
            if (BoyFrame - 103 < 0)
                goto remove_mower;
            if (BoyFrame - 105 <= 0) {
                state = 1;
            } else {
                if (BoyFrame - 109 < 0)
                    goto remove_mower;
                if (BoyFrame - 111 > 0)
                    goto remove_mower;
                state = 2;
            }
            goto positioned;
remove_mower:
            if (mowerObject == -1)
                return;
            hanim_RemoveAnimObject(yardAnimHandle, mowerObject, "mower");
            mowerObject = -1;
            return;
        }
    }
positioned:

    if (state == 0) {
        bx = 0x62;
        dx = 0xb5;
    } else if (state == 1) {
        bx = BoyX + 0x13;
        dx = BoyY + 0xf;
    } else {
        bx = BoyX - 0xf;
        dx = BoyY + 0xf;
    }

    if (mowerObject != -1)
        hanim_SetObjectPos(bx, dx, state + 0x2260, yardAnimHandle, mowerObject, -1);
    else
        mowerObject = hanim_AddAnimObject(yardAnimHandle, bx, dx, state + 0x2260, -1);
}
