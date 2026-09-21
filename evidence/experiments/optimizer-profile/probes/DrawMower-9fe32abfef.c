/*
 * DrawMower: keep the yard's lawnmower animation object in step with the
 * boy.  While BoyHere is 3 or 4 (the boy is mowing) the mower sound
 * myBeginSound(0x40, 0, 0x24) is started unless the game is paused, and
 * the boy's walk frame selects the mower state: frames 103..105 put the
 * mower ahead-right (state 1, BoyX+19), frames 109..111 ahead-left
 * (state 2, BoyX-15), both at BoyY+15; any other frame removes the shown
 * mower object (tag "mower", DGROUP 0x1954) and clears the private
 * handle (mowerObject, -1 sentinel at DGROUP 0x1890).  Outside 3/4 the
 * mower stays parked at its fixed spot (0x62, 0xb5), state 0.  The
 * object (frame set 0x2260 + state) is created on first use and
 * repositioned afterwards.
 *
 * Unit profile /Og: the frame switch lowers to MSC's SUB/JL/JO/DEC/DEC/JLE
 * range chains, and the two "BoyY + 15" tails are cross-jumped.
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
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

void far DrawMower(void)
{
    int state;
    register int right;
    register int bottom;

    state = 0;
    if (BoyHere == 3 || BoyHere == 4) {
        if (GamePaused == 0)
            myBeginSound(0x40, 0, 0x24);
        switch (BoyFrame) {
        case 103:
        case 104:
        case 105:
            state = 1;
            break;
        case 109:
        case 110:
        case 111:
            state = 2;
            break;
        default:
            if (mowerObject != -1) {
                hanim_RemoveAnimObject(yardAnimHandle, mowerObject, "mower");
                mowerObject = -1;
            }
            return;
        }
    }

    if (state == 0) {
        right = 0x62;
        bottom = 0xb5;
    } else if (state == 1) {
        right = BoyX + 0x13;
        bottom = BoyY + 0xf;
    } else {
        right = BoyX - 0xf;
        bottom = BoyY + 0xf;
    }

    if (mowerObject != -1)
        hanim_SetObjectPos(right, bottom, state + 0x2260, yardAnimHandle, mowerObject, -1);
    else
        mowerObject = hanim_AddAnimObject(yardAnimHandle, right, bottom, state + 0x2260, -1);
}
