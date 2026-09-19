/* Candidate reconstruction of the discardability classification wrapper. */
extern unsigned int far pascal GlobalFlags(unsigned int handle);

int mem_Type(unsigned int handle)
{
    return 3 + (((GlobalFlags(handle) & 0x100) == 0) ? -2 : 0);
}
