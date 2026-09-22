/*
 * initControls: one-time setup for the caste/mode control windows.  Probes
 * the "knob" bitmap size (gr_BitMapSize(&knobSize, 0x578)) and object
 * 0x120d's rect (the result is unused beyond the call's side effect, as in
 * the admitted twins), forces ModeAuto/CasteAuto on and
 * ShowPercentMode/ShowPercentCaste on, resets the mode/caste button-state
 * words to -1, and seeds the live edit buffers (modeLevels, casteLevels)
 * and each window's set-0 default-level slot (modeSetLevels[0],
 * casteSetLevels[0]) from the mode/caste default level templates
 * (modeLevelDefaults, casteLevelDefaults) word by word.
 */
struct WinRect { int left; int top; int right; int bottom; };
struct BitmapSize { int width; int height; };

extern struct BitmapSize far knobSize;
extern int far ModeAuto;
extern int far CasteAuto;
extern int far ShowPercentMode;
extern int far ShowPercentCaste;
extern int far modeButtonState;
extern int far casteButtonState;
extern int far modeLevels[3];
extern int far modeLevelDefaults[3];
extern int far modeSetLevels[][3];
extern unsigned int far casteLevels[];
extern int far casteLevelDefaults[3];
extern int far casteSetLevels[][3];

extern int far IdealCaste[];

extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_ModeControlChanged(void);
extern void far win_CasteControlChanged(void);

#define HUNDRED 100UL
#define FIFTY 50UL

void far initControls(void)
{
    struct WinRect rect;
    int i;

    gr_BitMapSize(&knobSize, 0x578);
    win_GetObjRect(0x120d, &rect);

    ModeAuto = 1;
    CasteAuto = 1;
    ShowPercentMode = 1;
    ShowPercentCaste = 1;
    modeButtonState = 0xffff;
    casteButtonState = 0xffff;

    for (i = 0; i < 3; i++) {
        modeLevels[i] = modeLevelDefaults[i];
        modeSetLevels[0][i] = modeLevelDefaults[i];
        casteLevels[i] = casteLevelDefaults[i];
        casteSetLevels[0][i] = casteLevelDefaults[i];
    }

    win_ModeControlChanged();
    win_CasteControlChanged();

    IdealCaste[0] = (HUNDRED * casteLevels[1] + 0x3fff) / 0xffff;
    IdealCaste[1] = (HUNDRED * casteLevels[2] + 0x3fff) / 0xffff;
    IdealCaste[2] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
    IdealCaste[3] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
}
