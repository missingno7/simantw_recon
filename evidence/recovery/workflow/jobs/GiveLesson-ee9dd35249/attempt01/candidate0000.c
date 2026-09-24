/*
 * GiveLesson dispatches the one-based tutorial lesson number to its SHARED
 * string object and optional MWINNT picture, forcing each dialog.  The
 * callers Feedback and RunTutor pass TutLesson.  A few lessons also update
 * the tutorial counters/timers, apply a health/ant-count change, or clear
 * the 0x800-byte PherMapA table.
 */
extern void far PictStrnDialog(int picture, int object, int force);
extern void far AddBlackAnts(int count);
extern void far SetMyHealth(int health);
extern long far MacTickCount(void);
extern int near MeLocX;
extern int near MeLocY;
extern int far TilesDugB;
extern long far TimeTemp;
extern int far LessonTemp;
extern int far modeLevels[2];
extern int far TutLesson;
extern unsigned int far PherMapA[64][16];

void far GiveLesson(int lesson)
{
    int row;
    int col;

    switch (lesson) {
    case 1:
        PictStrnDialog(0, 0x2af8, 1);
        return;
    case 2:
        PictStrnDialog(0x4268, 0x2afa, 1);
        return;
    case 3:
        PictStrnDialog(0, 0x2afc, 1);
        TimeTemp = TilesDugB + 2;
        return;
    case 4:
        PictStrnDialog(0, 0x2afe, 1);
        TimeTemp = TilesDugB + 10;
        return;
    case 5:
        PictStrnDialog(0x4269, 0x2b00, 1);
        return;
    case 6:
        PictStrnDialog(0, 0x2b02, 1);
        return;
    case 7:
        PictStrnDialog(0, 0x2b04, 1);
        LessonTemp = MeLocY + MeLocX;
        TimeTemp = MacTickCount() + 0x258L;
        return;
    case 8:
        PictStrnDialog(0, 0x2b06, 1);
        LessonTemp = 0;
        return;
    case 9:
        PictStrnDialog(0, 0x2b08, 1);
        LessonTemp = modeLevels[0] + modeLevels[1];
        TimeTemp = MacTickCount() + 0x258L;
        return;
    case 10:
        PictStrnDialog(0, 0x2b0a, 1);
        return;
    case 11:
        PictStrnDialog(0x4276, 0x2b0c, 1);
        return;
    case 12:
        PictStrnDialog(0, 0x2b0e, 1);
        return;
    case 13:
        PictStrnDialog(0x426a, 0x2b10, 1);
        return;
    case 14:
        PictStrnDialog(0x426a, 0x2b12, 1);
        SetMyHealth(8);
        return;
    case 15:
        PictStrnDialog(0, 0x2b14, 1);
        return;
    case 16:
        PictStrnDialog(0, 0x2b16, 1);
        return;
    case 17:
        PictStrnDialog(0x4275, 0x2b18, 1);
        return;
    case 18:
        PictStrnDialog(0x426b, 0x2b1a, 1);
        return;
    case 19:
        PictStrnDialog(0, 0x2b1c, 1);
        return;
    case 20:
        PictStrnDialog(0, 0x2b1e, 1);
        return;
    case 21:
        PictStrnDialog(0x426c, 0x2b20, 1);
        return;
    case 22:
        PictStrnDialog(0, 0x2b22, 1);
        return;
    case 23:
        AddBlackAnts(10);
        PictStrnDialog(0, 0x2b24, 1);
        return;
    case 24:
        PictStrnDialog(0, 0x2b26, 1);
        return;
    case 25:
        PictStrnDialog(0, 0x2b28, 1);
        return;
    case 26:
        PictStrnDialog(0, 0x2b2a, 1);
        LessonTemp = MeLocY + MeLocX;
        TimeTemp = MacTickCount() + 0x258L;
        return;
    case 27:
        PictStrnDialog(0, 0x2b2c, 1);
        LessonTemp = MeLocY + MeLocX;
        return;
    case 28:
        PictStrnDialog(0, 0x2b2e, 1);
        return;
    case 29:
        PictStrnDialog(0, 0x2b30, 1);
        return;
    case 30:
        PictStrnDialog(0, 0x2b32, 1);
        LessonTemp = 0;
        return;
    case 31:
        PictStrnDialog(0, 0x2b34, 1);
        return;
    case 32:
        PictStrnDialog(0, 0x2b36, 1);
        return;
    case 33:
        PictStrnDialog(0x426d, 0x2b38, 1);
        return;
    case 34:
        PictStrnDialog(0, 0x2b3a, 1);
        return;
    case 35:
        PictStrnDialog(0, 0x2b3c, 1);
        return;
    case 36:
        PictStrnDialog(0x426e, 0x2b3e, 1);
        return;
    case 37:
        PictStrnDialog(0, 0x2b40, 1);
        return;
    case 38:
        PictStrnDialog(0x426f, 0x2b42, 1);
        return;
    case 39:
        PictStrnDialog(0x4270, 0x2b44, 1);
        return;
    case 40:
        PictStrnDialog(0x4270, 0x2b46, 1);
        return;
    case 41:
        PictStrnDialog(0x4270, 0x2b48, 1);
        LessonTemp = modeLevels[0] + modeLevels[1];
        return;
    case 42:
        PictStrnDialog(0, 0x2b4a, 1);
        return;
    case 43:
        ++TutLesson;
        PictStrnDialog(0x4271, 0x2b4e, 1);
        return;
    case 44:
        PictStrnDialog(0x4271, 0x2b4e, 1);
        return;
    case 45:
        PictStrnDialog(0x4272, 0x2b50, 1);
        return;
    case 46:
        PictStrnDialog(0x4272, 0x2b52, 1);
        LessonTemp = 0;
        return;
    case 47:
        PictStrnDialog(0x4273, 0x2b54, 1);
        return;
    case 48:
        PictStrnDialog(0x4273, 0x2b56, 1);
        return;
    case 49:
        PictStrnDialog(0, 0x2b58, 1);
        AddBlackAnts(0x50);
        for (row = 0; row < 64; ++row)
            for (col = 0; col < 16; ++col)
                PherMapA[row][col] = 0;
        return;
    case 50:
        PictStrnDialog(0x4274, 0x2b5a, 1);
        LessonTemp = 0;
        return;
    case 51:
        PictStrnDialog(0, 0x2b5c, 1);
        return;
    case 52:
        PictStrnDialog(0, 0x2b5e, 1);
        return;
    case 53:
        PictStrnDialog(0, 0x2b60, 1);
        return;
    case 54:
        PictStrnDialog(0, 0x2b62, 1);
        return;
    case 55:
        if (LessonTemp == 0)
            PictStrnDialog(0, 0x2b64, 1);
        else
            PictStrnDialog(0, 0x2b66, 1);
        return;
    case 56:
        PictStrnDialog(0, 0x2b68, 1);
        return;
    }
}
