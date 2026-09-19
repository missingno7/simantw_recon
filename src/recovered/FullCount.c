/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern void far CountAnts(void);
extern void far Feedback(void);

void FullCount(void)
{
    CountAnts();
    Feedback();
}
