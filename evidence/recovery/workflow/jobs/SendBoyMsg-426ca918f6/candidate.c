/*
 * A boy message in the normal message range starts a short timeout.  The
 * timeout is measured from the current Macintosh tick count, while the
 * message code is kept in the simulation state for the next boy update.
 * Values above 22 are not scheduled by this helper.
 */
struct BoyClock {
    unsigned char pad[0x7d4a];
    unsigned long ticks;
};

struct BoyMessageState {
    unsigned char pad[0x99da];
    unsigned int active;
};

struct BoyState {
    unsigned char pad[0x72f2];
    unsigned int message;
};

extern struct BoyClock far boyClock;
extern struct BoyMessageState far boyMessageState;
extern struct BoyState far boyState;
extern unsigned long far MacTickCount(void);

void SendBoyMsg(int message)
{
    if (message <= 0x16) {
        boyClock.ticks = MacTickCount() + 0x12cL;
        boyMessageState.active = 1;
        boyState.message = message;
    }
}
