/*
 * Hypothesis: service the Windows queue only while songs are enabled and
 * the four-word multimedia state is installed, idle, and has a song queued.
 * The state is the independently resolved private SIMANT_DATA_GROUP block
 * observed at ES:8d08..8d0e; its selector must remain live only on the
 * songsOnFlag-positive path.  The local is the 18-byte Win16 MSG record.
 */
struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};

extern int near songsOnFlag;
extern int far pascal PeekMessage(struct MSG far *message,
                                  int hwnd, unsigned int first,
                                  unsigned int last, unsigned int remove);

struct MultimediaState {
    int moduleHandle;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
    unsigned int songState;
};
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)

void myServiceSong(void)
{
    struct MSG message;
    int service;

    if (!songsOnFlag)
        service = 0;
    else if (stateViaSelector.moduleHandle == 0 || stateViaSelector.soundInstalled == 0 ||
             stateViaSelector.waveInstalled != 0 || stateViaSelector.midiHandle == 0)
        service = 0;
    else
        service = 1;

    if (service)
        PeekMessage(&message, 0, 0, 0, 0);
}
