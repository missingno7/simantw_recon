/* Candidate reconstruction of the event-flush thunk. */
extern void far win_FlushEvents(void);

void ButtonHeldEnd(void)
{
    win_FlushEvents();
}
