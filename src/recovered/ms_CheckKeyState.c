/* Byte-matched reconstruction of the USER GetAsyncKeyState predicate. */
extern int far pascal GetAsyncKeyState(unsigned int key);

int ms_CheckKeyState(unsigned int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}
