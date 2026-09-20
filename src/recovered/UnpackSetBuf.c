extern void far * near unpackHandle;

void UnpackSetBuf(void far *buffer, unsigned int size)
{
    (&unpackHandle)[-1] = buffer;
    ((unsigned int *)&unpackHandle)[-3] = size;
}
