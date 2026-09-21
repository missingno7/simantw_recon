/*
 * Hypothesis: each database slot occupies 0x7c bytes in match_position.
 * An active slot owns a file handle at +0x7480/+0x7482; close it after
 * rewinding and writing the 14-byte name area at +0x7470, then close the
 * logical index and clear its openDBData byte at +0x7408.
 */
extern unsigned char far match_position[];
extern unsigned char far openDBData[];
extern long far pascal llseek(int handle, long offset, int origin);
extern int far pascal lwrite(int handle, char far *buffer, unsigned int count);
extern int far pascal lclose(int handle);
extern void far CloseIndex(int index);

void far CloseDB(int index)
{
    int record;
    int handle;

    record = index * 0x7c;
    handle = *(int far *)(match_position + record + 0x7480);
    if (*(int far *)(match_position + record + 0x7482) != 0) {
        llseek(handle, 0L, 0);
        lwrite(handle, (char far *)(match_position + record + 0x7470),
               0x0e);
        lclose(handle);
        CloseIndex(index);
        openDBData[record + 0x7408] = 0;
    }
}
