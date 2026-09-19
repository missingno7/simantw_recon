/* Candidate reconstruction of the reverse sound wrapper. */
extern void far myBeginSound(unsigned int first,
                             unsigned int second,
                             unsigned int third);

void myBeginSoundReverse(unsigned int first,
                         unsigned int second,
                         unsigned int third)
{
    myBeginSound(first, second, third);
}
