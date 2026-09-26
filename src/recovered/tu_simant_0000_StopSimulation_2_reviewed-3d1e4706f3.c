/* Candidate translation unit simant_0000: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _StopSimulation, _RestartSimulation */

extern int near rootWnd;
extern int far pascal KillTimer(int window, unsigned int timer);
extern int far pascal PeekMessage(void far *message, int window,
                                  unsigned int first, unsigned int last,
                                  unsigned int remove);
static void (far *near lpTimerFunc)(void) = 0;
static int simulationStops = 0;
extern int far pascal SetTimer(int window, unsigned int timer,
                               unsigned int interval,
                               void (far *timerFunc)(void));

void StopSimulation(void)
{
    unsigned char message[18];

    if (simulationStops == 0) {
        KillTimer(rootWnd, 0);
        while (PeekMessage(message, 0, 0x113, 0x113, 3))
            ;
    }
    ++simulationStops;
}

void RestartSimulation(void)
{
    --simulationStops;
    if (simulationStops == 0)
        SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
}

