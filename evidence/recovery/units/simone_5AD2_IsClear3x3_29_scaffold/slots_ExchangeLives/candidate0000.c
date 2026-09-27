/*
 * ExchangeLives: perform the life-exchange lesson step.  The lesson flag is
 * raised, then DoLifeExchange decides the outcome.  On success (result 1)
 * the current game tool is cleared, the game is paused according to the
 * saved pause state, and if the player is the yellow queen (MeType 0x60)
 * the success sound is played while the edit view is redrawn and the
 * sound is allowed to finish (polling every five ticks) before the victory
 * song starts; any other player type just plays the success sound.  A
 * failed exchange plays the failure sound instead.
 */
extern int far LessonTemp;
extern int far CurGameTool;
extern int far SaveGamePaused;
extern int near MeType;

extern int far DoLifeExchange(int a, int b, int c);
extern void far PauseGame(int paused);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far DoEditUpdateDraw(void);
extern int far mySoundIsDone(void);
extern void far myDelay(unsigned long ticks);
extern void far myBeginSong(unsigned int song, unsigned int priority);

void far ExchangeLives(int a, int b, int c)
{
    LessonTemp = 1;
    if (DoLifeExchange(a, b, c) == 1) {
        CurGameTool = -1;
        PauseGame(SaveGamePaused);
        if (MeType == 0x60) {
            myBeginSound(0xf, 0, 0x7e);
            DoEditUpdateDraw();
            while (!mySoundIsDone())
                myDelay(5L);
            myBeginSong(0x2afe, 0x7e);
        } else
            myBeginSound(0xf, 0, 0x7e);
    } else
        myBeginSound(1, 0, 0x7e);
}
