/* Start a MIDI song by loading its database record, decoding its track data,
 * and preparing the Windows sound queue.  The private tail of the original
 * state block is still unnamed; this draft models the independently shared
 * header fields used by the neighboring multimedia routines. */
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
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) soundState = {0};
#define mmState (*(struct MultimediaState __based(mmSelector) *)&soundState)

extern int near songsOnFlag;
extern unsigned int far db_LoadObject(unsigned int object, unsigned int kind,
                                      unsigned int lock);
extern void far db_ReleaseHandle(unsigned int handle);
extern void far * mem_Lock(unsigned int handle);
extern unsigned long mem_Size(unsigned int handle);
extern void mem_Unlock(unsigned int handle);
extern unsigned short far FlipWord(unsigned short value);
extern unsigned long far FlipLong(unsigned long value);
extern unsigned long far ExtractVariableLen(unsigned char far **cursor,
                                             unsigned long far *remaining);
extern int far pascal OpenSound();
extern int far pascal CloseSound();
extern int far pascal SetVoiceQueueSize();
extern int far pascal SetVoiceNote();
extern int far pascal StartSound();
extern unsigned int far pascal GlobalAlloc(unsigned int flags, unsigned long bytes);
extern int far pascal GlobalPageLock(unsigned int handle);
extern int far pascal GlobalPageUnlock(unsigned int handle);
extern int far pascal GlobalWire(unsigned int handle);
extern int far pascal GlobalUnWire(unsigned int handle);
extern int far pascal GlobalFree(unsigned int handle);
extern char far * far pascal GetModuleFileName(unsigned int instance,
                                                char far *path,
                                                int maximum);
extern char far * far pascal strrchr(const char far *text, int ch);
extern int far sprintf(char far *buffer, const char far *format, ...);
extern void far WinPrintf(char far *text);

void far myBeginSong(unsigned int song, unsigned int priority)
{
    unsigned int handle;
    unsigned int sound;
    unsigned char far *track;
    unsigned long remaining;
    unsigned long delta;
    unsigned long fileSize;
    unsigned short tracks;
    unsigned short division;
    unsigned short eventLength;
    unsigned char status;
    unsigned char runningStatus;
    unsigned int voice;
    unsigned int channel;
    unsigned long ticks;
    int failed;

    if (mmState.moduleHandle == 0)
        return;
    if (songsOnFlag == 0)
        return;
    if (mmState.midiHandle == 0)
        return;

    handle = db_LoadObject(song, 9, 0);
    if (handle == 0)
        return;
    track = (unsigned char far *)mem_Lock(handle);
    if (track == 0) {
        db_ReleaseHandle(handle);
        return;
    }
    fileSize = mem_Size(handle);
    remaining = fileSize;
    failed = 0;
    runningStatus = 0;
    ticks = 0;

    if (remaining < 14 || track[0] != 'M' || track[1] != 'T' ||
        track[2] != 'h' || track[3] != 'd')
        failed = 1;
    if (!failed) {
        tracks = FlipWord(*(unsigned short far *)(track + 10));
        division = FlipWord(*(unsigned short far *)(track + 12));
        track += 14;
        remaining -= 14;
        OpenSound(mmState.midiHandle, 0);
        voice = priority;
        channel = tracks;
        SetVoiceQueueSize(voice, 0x100);
        while (remaining > 8 && channel != 0) {
            if (track[0] != 'M' || track[1] != 'T' ||
                track[2] != 'r' || track[3] != 'k') {
                failed = 1;
                break;
            }
            eventLength = FlipWord(*(unsigned short far *)(track + 4));
            track += 8;
            remaining -= 8;
            if ((unsigned long)eventLength > remaining) {
                failed = 1;
                break;
            }
            remaining = eventLength;
            while (remaining != 0) {
                delta = ExtractVariableLen(&track, &remaining);
                ticks += delta;
                status = *track++;
                remaining--;
                if (status < 0x80) {
                    track--;
                    remaining++;
                    status = runningStatus;
                } else {
                    runningStatus = status;
                }
                if (status == 0xff) {
                    unsigned char meta;
                    meta = *track++;
                    remaining--;
                    delta = ExtractVariableLen(&track, &remaining);
                    track += (unsigned int)delta;
                    remaining -= delta;
                    if (meta == 0x2f)
                        break;
                } else if (status == 0xf0 || status == 0xf7) {
                    delta = ExtractVariableLen(&track, &remaining);
                    track += (unsigned int)delta;
                    remaining -= delta;
                } else {
                    SetVoiceNote(voice, status & 0x0f,
                                 track[0], track[1], priority);
                    track += 2;
                    remaining -= 2;
                }
            }
            channel--;
        }
        if (!failed) {
            sound = GlobalAlloc(0x2000, (unsigned long)division * tracks);
            if (sound != 0) {
                GlobalPageLock(sound);
                GlobalWire(sound);
                StartSound();
                GlobalUnWire(sound);
                GlobalPageUnlock(sound);
                GlobalFree(sound);
            }
        }
    }
    mem_Unlock(handle);
    db_ReleaseHandle(handle);
    if (failed)
        CloseSound();
}
