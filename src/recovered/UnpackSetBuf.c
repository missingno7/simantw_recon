#define unpackSize (*(unsigned int near *)0xb8d6)
#define unpackBuffer (*(void far * near *)0xb8d8)

void UnpackSetBuf(void far *buffer, unsigned int size)
{
    unpackBuffer = buffer;
    unpackSize = size;
}
