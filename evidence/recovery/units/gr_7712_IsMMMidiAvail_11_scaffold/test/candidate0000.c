/* Candidate translation unit gr_7712_IsMMMidiAvail_11_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _IsMMMidiAvail, _IsMMWaveAvail, _MusicInit, _SysBeep, _myBeginSoundList, _ExtractDWord, _ExtractWord, _Extract24BitVal, _mySoundIsDone, _myBeginSoundReverse
 * SCAFFOLDED: claimed members in 5 code runs; no pool stand-ins were needed. */

typedef int (far *MMProc)(void);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
static int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;
extern char near wSoundBlasterMsg[];
extern void far WinPrintf(char far *text);
extern int far pascal MessageBeep(unsigned int type);
extern unsigned long far FlipLong(unsigned long value);
extern unsigned short FlipWord(unsigned short);
struct ThreeBytes {
    unsigned char b[3];
};
extern void far myBeginSound(unsigned int first,
                             unsigned int second,
                             unsigned int third);


void MusicInit(void);
void SysBeep(void);
void myBeginSoundList(void);
void ExtractDWord(void far * far *p, unsigned long far *out);
void ExtractWord(void far * far *p,unsigned short far *out);
void far Extract24BitVal(void far * far *cursor, unsigned long far *value, long far *remaining);
int mySoundIsDone(void);
void myBeginSoundReverse(unsigned int first, unsigned int second, unsigned int third);

#pragma alloc_text(RUN2_TEXT, MusicInit, SysBeep, myBeginSoundList)
#pragma alloc_text(RUN3_TEXT, ExtractDWord, ExtractWord)
#pragma alloc_text(RUN4_TEXT, Extract24BitVal)
#pragma alloc_text(RUN5_TEXT, mySoundIsDone, myBeginSoundReverse)

int IsMMMidiAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmModule, wSoundBlasterMsg + 6);
    if (proc)
        return proc();
    return 0;
}

int IsMMWaveAvail(void)
{
    MMProc proc;

    proc = GetProcAddress(mmModule, wSoundBlasterMsg + 0x18);
    if (proc)
        return proc();
    return 0;
}

void MusicInit(void)
{
    WinPrintf("MUSIC INIT!");
}

void SysBeep(void)
{
    MessageBeep(0);
}

void myBeginSoundList(void)
{
}

void ExtractDWord(void far * far *p, unsigned long far *out)
{
    *out = *(unsigned long far *)*p;
    *out = FlipLong(*out);
    *p = (void far *)((unsigned long)*p + 4);
}

void ExtractWord(void far * far *p,unsigned short far *out) { *out=*(unsigned short far *)*p; *out=FlipWord(*out); *p=(void far *)((unsigned long)*p+2); }

void far Extract24BitVal(void far * far *cursor, unsigned long far *value,
                         long far *remaining)
{
    *value = 0;
    *(struct ThreeBytes far *)((unsigned long)value + 1) =
        *(struct ThreeBytes far *)*cursor;
    *value = FlipLong(*value);
    *cursor = (void far *)((unsigned long)*cursor + 3);
    *remaining -= 3;
}

int mySoundIsDone(void)
{
    return 1;
}

void myBeginSoundReverse(unsigned int first,
                         unsigned int second,
                         unsigned int third)
{
    myBeginSound(first, second, third);
}

