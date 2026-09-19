/* Byte-matched reconstruction of the USER MessageBeep wrapper. */
extern int far pascal MessageBeep(unsigned int type);

void SysBeep(void)
{
    MessageBeep(0);
}
