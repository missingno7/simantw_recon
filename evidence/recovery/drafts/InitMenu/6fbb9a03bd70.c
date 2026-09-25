/*
 * Preserve the proven resource-object preamble of InitMenu: load object kind 6,
 * lock the returned handle, then unhook the object. The packet does not name
 * the function's menu-index word or its selector-backed menu tables, so this
 * scratch hypothesis intentionally contains no guessed menu-table access.
 */
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far *mem_Lock(unsigned int handle);
extern void far db_UnhookObject(int object, int kind);

int far InitMenu(int object)
{
    unsigned int handle;

    handle = db_LoadObject(object, 6, 0);
    if (handle == 0)
        return 0;
    mem_Lock(handle);
    db_UnhookObject(object, 6);
    return 1;
}
