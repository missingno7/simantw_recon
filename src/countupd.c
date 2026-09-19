/* Small simulation feedback wrapper, retained as an isolated matching probe. */
extern void far Feedback(void);

void far CountUpdate(void)
{
    Feedback();
}
