typedef void (far *Hook)(void);

extern Hook near cacheHook;
extern Hook near releaseHook;

void ch_SetCacheHooks(Hook cache, Hook release)
{
    cacheHook = cache;
    releaseHook = release;
}
