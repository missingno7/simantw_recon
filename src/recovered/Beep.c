/* Byte-matched reconstruction of the USER MessageBeep wrapper. */
extern int far pascal MessageBeep(unsigned int type);

void Beep(void)
{
    MessageBeep(0);
}
