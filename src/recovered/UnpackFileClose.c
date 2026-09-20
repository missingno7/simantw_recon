/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern int near unpackHandle;
extern int far close(int handle);

void UnpackFileClose(void)
{
    close(unpackHandle);
}
