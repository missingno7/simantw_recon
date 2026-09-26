/* Both cache hooks are far callbacks set by ch_SetCacheHooks. */
typedef void (far *CacheHook)(void);
CacheHook cacheHook = 0;
