/* Candidate reconstruction of the balloon pre-draw thunk. */
extern void far DrawCurBalloons(void);

void PreDrawBalloons(void)
{
    DrawCurBalloons();
}
