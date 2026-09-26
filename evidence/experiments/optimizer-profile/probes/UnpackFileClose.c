extern int near unpackHandle;
extern void far pascal close(int handle);

void UnpackFileClose(void)
{
    close(unpackHandle);
}
