/* Candidate translation unit gr_0000_InitGraphics_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitGraphics
 * SCAFFOLDED: unclaimed members _SetHelpCursor, _IBMInitStuff are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far pascal GetDesktopWindow(void);
extern int far pascal GetDC(int window);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal ReleaseDC(int window, int dc);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far WinPrintf(char far *format, ...);
extern void far db_SetDataBase(char far *text);
extern signed char near displayType;

extern int far match_position;  /* scaffold reference for pool word C69C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C69E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C6A0 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C6A2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C6A4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C6A6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C6A8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C6AA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C6AC (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_SetHelpCursor(void);
void far pool_stub_IBMInitStuff(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetHelpCursor)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_IBMInitStuff)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetHelpCursor.
 * It only reproduces the object's selector-pool allocation order for the
 * words C69C C69E C6A0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetHelpCursor(void)
{
    volatile int t;

    t = match_position;
    t = match_length;
    t = Dx8;
}

void far InitGraphics(char far *labels)
{
    int window;
    int dc;
    int detectedType;
    char buffer[100];
    char far * volatile displayNames[11] = {
        "hcega", "mono", "tdyga", "mono", "lcega", "mono",
        "l256", "mono", "hcega", "mwin", "winga"
    };

    if ((unsigned char)displayType == 0xff) {
        window = GetDesktopWindow();
        dc = GetDC(window);
        if (GetDeviceCaps(dc, 12) == 1 &&
            GetDeviceCaps(dc, 14) == 1) {
            ReleaseDC(window, dc);
            detectedType = 9;
        } else {
            ReleaseDC(window, dc);
            detectedType = 10;
        }
        displayType = (unsigned char)detectedType;
    }

    sprintf(buffer, "%s%s", displayNames[displayType], labels);
    WinPrintf("db_SetDataBase: %s\n", buffer);
    db_SetDataBase(buffer);
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _IBMInitStuff.
 * It only reproduces the object's selector-pool allocation order for the
 * words C6A2 C6A4 C6A6 C6A8 C6AA C6AC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_IBMInitStuff(void)
{
    volatile int t;

    t = Dy8;
    t = pack_buf;
    t = Dx9;
    t = Scycle;
    t = EditColumns;
    t = Dy9;
}

