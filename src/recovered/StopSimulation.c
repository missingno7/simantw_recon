static int simulationStops = 0;

extern int near rootWnd;
extern int far pascal KillTimer(int window, unsigned int timer);
extern int far pascal PeekMessage(void far *message, int window,
                                  unsigned int first, unsigned int last,
                                  unsigned int remove);

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
