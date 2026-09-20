extern int near unpackHandle;
extern int far pascal close(int handle);

void UnpackFileClose(void)
{
    close(unpackHandle);
}
