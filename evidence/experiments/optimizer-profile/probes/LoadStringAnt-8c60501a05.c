/*
 * LoadStringAnt: load resource id (type 4) via db_LoadObject, lock it,
 * and parse it into a malloc'd NUL-terminated far-pointer string table.
 * The locked resource's second byte is the string count; strings follow
 * as length-prefixed byte runs. On load failure, WinPrintf logs and NULL
 * is returned. Each string's length byte is stripped in place via
 * memmove and the remainder NUL-terminated; table[i] points at the
 * string bytes, and table[count] is NULL. The resource is unlocked
 * before returning the table. Reconstructed with moderate confidence
 * given this unit's other members are not yet admitted for comparison.
 */
extern int far db_LoadObject(int id, int type, int flags);
extern void far WinPrintf(char far *fmt, int arg);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far *malloc(unsigned int size);
extern void far *memmove(void far *dest, void far *src, unsigned int n);

void far *LoadStringAnt(int id)
{
    int handle;
    unsigned char far *data;
    char far * far *table;
    int count;
    int i;
    unsigned char far *p;
    int len;

    handle = db_LoadObject(id, 4, 0);
    if (handle == 0) {
        WinPrintf("LoadStringAnt failed, id=%d", id);
        return 0;
    }
    data = mem_Lock(handle);
    count = data[1];
    p = data + 2;
    table = malloc((count + 1) * 4);
    if (count > 0) {
        for (i = 0; i < count; i++) {
            len = *p;
            table[i] = (char far *)(p + 1);
            memmove(p, p + 1, len);
            p[len] = 0;
            p += len + 1;
        }
    }
    table[count] = 0;
    mem_Unlock(handle);
    return table;
}
