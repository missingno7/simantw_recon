/*
 * MakeBark: let the yard dog bark.  Only while the map is not being
 * shown (far MapMode 0), the yard is in a normal mode (YardMode below 2)
 * and the tick count has passed the far long DogBarkDelay does a bark
 * play: kinds 0 and 2 use sound 0x16, kind 1 sound 0x15 and kind 3 sound
 * 0x17, each with the caller's third sound argument; other kinds are
 * silent.  The delay is then re-armed to now plus 60 ticks plus a random
 * 0..29.
 */
extern int far MapMode;
extern int near YardMode;
extern long far DogBarkDelay;

extern long far MacTickCount(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far SRand1(int range);

void far MakeBark(int kind, int level)
{
    if (MapMode == 0 && YardMode < 2 && MacTickCount() > DogBarkDelay) {
        switch (kind) {
        case 3:
            myBeginSound(0x17, 0, level);
            break;
        case 1:
            myBeginSound(0x15, 0, level);
            break;
        case 0:
        case 2:
            myBeginSound(0x16, 0, level);
            
        }
        DogBarkDelay = SRand1(30) + MacTickCount() + 60;
    }
}
