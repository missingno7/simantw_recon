/*
 * ClearBookmarks: reset the seven bookmark records and their ribbon
 * buttons.  bookMark is the far SIMANT_DATA_GROUP table of seven 10-byte
 * records (MAPSYM 0x8aa0, bounded by userButtonHelpId at 0x8ae6; selector
 * slot 0xbe7a): the object number word is set to -1 and the remaining
 * word, long and word fields are zeroed (the long is stored as two zero
 * words from AX and CX).  For each record index i the "set" button
 * 0x2218 + i and the "go" button 0x2313 + i get the empty button bitmaps
 * 0x3899 + i (up) and 0x3867 + i (down) through the verified far
 * win_SetButtonBitmaps and are deselected with win_SetObjSelectedState.
 * The records are indexed; the loop optimizer reduces the index to a
 * record offset in SI compared unsigned against the end of the table,
 * with the segment loaded once from the selector slot.
 */
struct BookMark {
    int object;
    int plane;
    long position;
    int flags;
};

extern struct BookMark far bookMark[];
extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp,
                                     unsigned int bitmapDown);
extern void far win_SetObjSelectedState(int object, int selected);

void far ClearBookmarks(void)
{
    int i;

    for (i = 0; i < 7; i++) {
        bookMark[i].object = -1;
        bookMark[i].plane = 0;
        bookMark[i].position = 0L;
        bookMark[i].flags = 0;
        win_SetButtonBitmaps(0x2218 + i, 0x3899 + i, 0x3867 + i);
        win_SetObjSelectedState(0x2218 + i, 0);
        win_SetButtonBitmaps(0x2313 + i, 0x3899 + i, 0x3867 + i);
        win_SetObjSelectedState(0x2313 + i, 0);
    }
}

