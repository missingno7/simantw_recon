/* Candidate translation unit simtwo_BD5A: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_DrawBitMap */

extern unsigned int far db_LoadObject(int object, int type, int flags);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void db_ReleaseObject(unsigned int object, int type);
extern void far GPutPacked(int x, int y, void far *data);
extern void GPutImg(int x, int y, unsigned char far *image, int mask);
extern void far GPutPic(int x, int y, unsigned char far *picture, int mask);
extern void far WinPrintf(char far *format, ...);

int far win_DrawBitMap(int x, int y, int bitmapNumber)
{
  unsigned int handle;
  int far *data;
  int mask;
  handle = db_LoadObject(bitmapNumber, 2, 0);
  if (handle)
  {
    data = (int far *) mem_Lock(handle);
    if ((*data) == (-1)) {
        GPutPacked(x, y, data);
        mem_Unlock(handle);
        db_ReleaseObject(bitmapNumber, 2);
        return 1;
    }
    if ((*data) == 0x8000) {
        GPutPacked(x, y, data);
    } else if ((*data) == 0) {
        if ((((unsigned char far *)data)[2] & 0x7f) == 1) {
            mask = (((unsigned char far *)data)[2] & 0x80) ? 0 : 1;
            GPutImg(x, y, ((unsigned char far *)data) + 8, mask);
        } else {
            mask = (((unsigned char far *)data)[2] & 0x80) ? 0 : 1;
            GPutPic(x, y, ((unsigned char far *)data) + 8, mask);
        }
    } else if ((*data) == 3) {
        WinPrintf("win_DrawBitMap(bmtype_picandmsk)\n");
    }
    mem_Unlock(handle);
    db_ReleaseObject(bitmapNumber, 2);
    return 1;
  }
  else
    return 0;
}

