static void (far *near lpTimerFunc)(void) = 0;
static int simulationStops = 0;

extern int near rootWnd;
extern int far pascal SetTimer(int window, unsigned int timer,
                               unsigned int interval,
                               void (far *timerFunc)(void));

void RestartSimulation(void)
{
    --simulationStops;
    if (simulationStops == 0)
        SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
}
