extern int near db_numOfHandles;
extern int far db_handles[];
extern int far DBRecall(int position, int object, int kind, int far *out);
extern void far mem_Free(int handle);

int db_GetObjectSize(char far *name)
{
    int size;
    int handle;
    int index;

    for (index = 0; index < db_numOfHandles; ++index) {
        handle = DBRecall(db_handles[index], name, &size);
        if (handle) {
            mem_Free(handle);
            return size;
        }
    }
    return 0;
}
