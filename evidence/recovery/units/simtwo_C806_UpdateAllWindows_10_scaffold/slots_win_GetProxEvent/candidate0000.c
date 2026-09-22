/* Byte-matched reconstruction using the named last-proximity global. */
extern unsigned int near lastProxObj;

unsigned int win_GetProxEvent(void)
{
    return lastProxObj;
}
