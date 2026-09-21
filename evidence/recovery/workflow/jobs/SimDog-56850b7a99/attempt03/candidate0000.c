/*
 * SimDog: advance the yard dog's per-frame state machine.
 *
 * DogTurnCnt is decremented every call; only when it goes negative does
 * the dog pick a new heading (DogDir) and re-arm DogTurnCnt to 4. The
 * turn counter, dog X/Y sub-position and heading are each addressed
 * through a far pointer local across the branches below (single-element
 * far array names, decayed to a pointer, matching the AddAntToBList
 * Dx8-pointer idiom already admitted in this corpus), matching the
 * target's explicit bp-relative (offset,segment) pointer storage.
 *
 * Heading pick, CatOn!=0 (chasing the cat away): DogPx<5 -> 1; DogPx in
 * [5,8] -> 0 if DogPy>0, else YardCycle&3; DogPx>8 -> 3.
 *
 * Heading pick, CatOn==0 (wandering toward the boy), only when
 * NodeNum>=0x26: deltaX=DogPx-BoyPx, deltaY=DogPy-BoyPy. While both
 * |deltaX|>=1 and |deltaY|>=1, indoors (MapMode==0), the yard is normal
 * (YardMode<2) and the tick count has passed DogBarkDelay, the dog may
 * bark (myBeginSound 0x15) and DogBarkDelay is re-armed
 * SRand1(30)+MacTickCount()+60. Then: if both |deltaX|<2 and |deltaY|<2,
 * heading = YardCycle&3; else if deltaY<0 -> 2; deltaY>1 -> 0; deltaX<0
 * -> 1; deltaX>1 -> 3; otherwise YardCycle&3. Otherwise (NodeNum<0x26)
 * heading = (SRand1(3)+DogDir-1)&3.
 *
 * Movement: if DogDir==1 and SRand1(10)==0, DogDir becomes a running
 * heading SRand2()+4 and DogTurnCnt=6. The per-heading magnitude table
 * (dirMagnitude, plus a YardCycle-based jitter while walking, DogDir<=3,
 * or a YardCycle&1 jitter while running) becomes the new DogFrame value.
 * DogY/DogX advance by the per-heading delta tables; DogPy/DogPx are
 * rederived from the new position (row/column division) and clamped to
 * [0,15]/[0,11], each edge re-biasing DogDir back toward the yard.
 *
 * Around DogFrame 100-103, a second bark opportunity (SRand1(6)==0,
 * indoors, normal yard mode, tick count past DogBarkDelay) plays a sound
 * chosen by SRand4() (0/2 -> 0x17, 1 -> 0x15, 3 -> 0x16, else silent)
 * and re-arms DogBarkDelay the same way.
 */
extern int near CatOn;
extern int near YardMode;
extern int far DogPx[];
extern int far DogPy[];
extern int far BoyPx;
extern int far BoyPy;
extern int far NodeNum;
extern int far DogDir[];
extern int far DogTurnCnt[];
extern int far BoyIsMowing;
extern int far MapMode;
extern int far YardCycle;
extern long far DogBarkDelay;
extern int near DogX;
extern int near DogY;
extern int near DogFrame;

extern int far SRand1(int range);
extern int far SRand2(void);
extern int far SRand4(void);
extern long far MacTickCount(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

static signed char near dirDeltaX[6] = { 0, 0, 0, 0, 0, 0 };
static signed char near dirDeltaY[6] = { 0, 0, 0, 0, 0, 0 };
static signed char near dirJitter[4] = { 0, 0, 0, 0 };
static signed char near dirMagnitude[6] = { 0, 0, 0, 0, 0, 0 };

void far SimDog(void)
{
    int far *turnCntPtr;
    int far *dogPxPtr;
    int far *dogDirPtr;
    int far *dogPyPtr;
    int deltaX;
    int absDeltaX;
    int deltaY;
    int absDeltaY;
    int heading;
    int kind;
    int frame;
    int savedPy;

    turnCntPtr = DogTurnCnt;
    if (--(*turnCntPtr) >= 0)
        goto move;

    if (CatOn != 0) {
        dogPxPtr = DogPx;
        if (*dogPxPtr < 5) {
            heading = 1;
        } else if (*dogPxPtr <= 8) {
            if (DogPy[0] > 0)
                heading = 0;
            else
                heading = YardCycle & 3;
        } else {
            heading = 3;
        }
    } else if (NodeNum >= 0x26) {
        deltaY = DogPy[0] - BoyPy;
        deltaX = DogPx[0] - BoyPx;
        absDeltaX = deltaX >= 0 ? deltaX : -deltaX;
        absDeltaY = deltaY >= 0 ? deltaY : -deltaY;

        if (absDeltaX >= 1 && absDeltaY >= 1 && BoyIsMowing == 0 &&
            MapMode == 0 && YardMode < 2 && MacTickCount() > DogBarkDelay) {
            kind = 1;
            switch (kind) {
            case 1:
                myBeginSound(0x15, 0, 0x7f);
                break;
            case 2:
                myBeginSound(0x17, 0, 0x7f);
                break;
            case 3:
                myBeginSound(0x16, 0, 0x7f);
                break;
            }
            DogBarkDelay = (long)SRand1(30) + MacTickCount() + 60;
        }

        if (absDeltaX < 2 && absDeltaY < 2)
            heading = YardCycle & 3;
        else if (deltaY < 0)
            heading = 2;
        else if (deltaY > 1)
            heading = 0;
        else if (deltaX < 0)
            heading = 1;
        else if (deltaX > 1)
            heading = 3;
        else
            heading = YardCycle & 3;
    } else {
        heading = (SRand1(3) + DogDir[0] - 1) & 3;
    }
    DogDir[0] = heading;
    *turnCntPtr = 4;

move:
    dogDirPtr = DogDir;
    if (*dogDirPtr == 1 && SRand1(10) == 0) {
        *dogDirPtr = SRand2() + 4;
        *turnCntPtr = 6;
    }

    dogDirPtr = DogDir;
    if (*dogDirPtr > 3) {
        frame = dirMagnitude[*dogDirPtr] + (YardCycle & 1);
    } else {
        frame = dirJitter[YardCycle & 3] + dirMagnitude[*dogDirPtr];
    }

    DogY += dirDeltaY[*dogDirPtr];
    dogPyPtr = DogPy;
    *dogPyPtr = (DogY - 0x26) / 10;
    savedPy = *dogPyPtr;
    DogX += dirDeltaX[*dogDirPtr];
    dogPxPtr = DogPx;
    *dogPxPtr = (DogY + DogX - 0xc8) / 0x1c;
    if (savedPy < 0)
        *dogPyPtr = 0;

    if (*dogPyPtr > 0xf)
        *dogPyPtr = 0xf;
    if (*dogPxPtr < 0)
        *dogPxPtr = 0;
    if (*dogPxPtr > 0xb)
        *dogPxPtr = 0xb;

    if (*dogPyPtr < 1)
        *dogDirPtr = 2;
    else if (*dogPyPtr > 0xe)
        *dogDirPtr = 0;

    if (*dogPxPtr > 0xa)
        *dogDirPtr = 3;
    else if (*dogPxPtr < 4)
        *dogDirPtr = 1;

    DogFrame = frame;
    if (frame < 0x64)
        return;
    if (frame > 0x67)
        return;
    if (SRand1(6) != 0)
        return;

    kind = SRand4();
    if (MapMode != 0)
        return;
    if (YardMode >= 2)
        return;
    if (MacTickCount() <= DogBarkDelay)
        return;

    switch (kind) {
    case 0:
    case 2:
        myBeginSound(0x17, 0, 5);
        break;
    case 1:
        myBeginSound(0x15, 0, 5);
        break;
    case 3:
        myBeginSound(0x16, 0, 5);
        break;
    }
    DogBarkDelay = (long)SRand1(30) + MacTickCount() + 60;
}
