extern unsigned long far pascal GlobalSize(unsigned handle);

unsigned long mem_Size(unsigned handle)
{
    if (handle)
        return GlobalSize(handle);
    return 0L;
}
