/* Candidate translation unit antedit_7022_ExpIncSmell_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ExpIncSmell
 * SCAFFOLDED: unclaimed members _processExp, _DoTool, _DropWall, _ExpDig are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near MapPlane;
extern unsigned char far ExpSubStates[];
#define PherMapBN ((unsigned char (far *)[32])((unsigned char far *)PherMapA + 0x1000))  /* pool word C27A: one object, MAPSYM _PherMapA+4096 */
#define PherMapBT ((unsigned char (far *)[32])((unsigned char far *)PherMapA + 0x1800))  /* pool word C27A: one object, MAPSYM _PherMapA+6144 */
#define PherMapRN ((unsigned char (far *)[32])((unsigned char far *)PherMapA + 0x2000))  /* pool word C27A: one object, MAPSYM _PherMapA+8192 */
#define PherMapRT ((unsigned char (far *)[32])((unsigned char far *)PherMapA + 0x2800))  /* pool word C27A: one object, MAPSYM _PherMapA+10240 */
extern unsigned char far PherMapA[64][32];
extern int far pascal GetAsyncKeyState(unsigned int key);
extern void far SmoothMany(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

extern int far ExpLastPnt;  /* scaffold reference for pool word C25E (segment 9, MAPSYM_SITE_NAME) */
extern int far match_position;  /* scaffold reference for pool word C260 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C262 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C264 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C266 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C268 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C26A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurExpTool;  /* scaffold reference for pool word C26C (segment 9, MAPSYM_SITE_NAME) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C26E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C272 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C274 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C276 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ListIndexB;  /* scaffold reference for pool word C278 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_processExp(void);
void far pool_stub_DoTool(void);
void far pool_stub_DropWall(void);
void far pool_stub_ExpDig(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_processExp)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoTool)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DropWall)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ExpDig)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _processExp.
 * It only reproduces the object's selector-pool allocation order for the
 * words C25E C260 C262 C264 C266 C268 C26A C26C C26E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_processExp(void)
{
    volatile int t;

    t = ExpLastPnt;
    t = match_position;
    t = match_length;
    t = pack_buf;
    t = Scycle;
    t = EditColumns;
    t = MiscStrs;
    t = CurExpTool;
    t = LastQueenPlane;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoTool.
 * It only reproduces the object's selector-pool allocation order for the
 * words C270; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoTool(void)
{
    volatile int t;

    t = ExpSubStates[0];
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DropWall.
 * It only reproduces the object's selector-pool allocation order for the
 * words C272 C274; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DropWall(void)
{
    volatile int t;

    t = Dx8;
    t = Dy8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ExpDig.
 * It only reproduces the object's selector-pool allocation order for the
 * words C276 C278 C27A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ExpDig(void)
{
    volatile int t;

    t = EditDragPnt;
    t = ListIndexB;
    t = PherMapA[0][0];
}

void far ExpIncSmell(int x, int y)
{
    int ry;
    int rx;
    int val;
    int valid;
    int writeVal;
    unsigned int b;

    if (MapPlane > 1)
        return;

    ry = y >> 1;
    rx = x >> 1;

    valid = (rx >= 0 && rx <= 0x3f && ry >= 0 && ry <= 0x1f);
    if (!valid) {
        val = -1;
        goto map_value_ready;
    }
    {
        switch ((char)ExpSubStates[5]) {
        case 0:
            b = PherMapBN[rx][ry];
            break;
        case 1:
            b = PherMapBT[rx][ry];
            break;
        case 2:
            b = PherMapRN[rx][ry];
            break;
        case 3:
            b = PherMapRT[rx][ry];
            break;
        case 4:
            b = PherMapA[rx][ry];
            break;
        }
        val = b;
    }
map_value_ready:

    if (GetAsyncKeyState(0x11) & 0x8000)
        val -= 0x28;
    else
        val += 0x46;

    if (val < 0)
        val = 0;
    if (val > 0xff)
        val = 0xff;

    writeVal = val;
    writeVal = val;
    valid = (rx >= 0 && rx <= 0x3f && ry >= 0 && ry <= 0x1f);
    if (valid) {
        if (writeVal > 0xff)
            writeVal = 0xff;
        switch ((char)ExpSubStates[5]) {
        case 0:
            PherMapBN[rx][ry] = (unsigned char)writeVal;
            break;
        case 1:
            PherMapBT[rx][ry] = (unsigned char)writeVal;
            break;
        case 2:
            PherMapRN[rx][ry] = (unsigned char)writeVal;
            break;
        case 3:
            PherMapRT[rx][ry] = (unsigned char)writeVal;
            break;
        case 4:
            PherMapA[rx][ry] = (unsigned char)writeVal;
            break;
        }
    }

    SmoothMany(rx, ry);
    myBeginSound(0x1b, 0, 0x7e);
}

