/* Candidate translation unit antedit_A998_DrawDog_1_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawDog
 * SCAFFOLDED: unclaimed members _DrawYardCursor, _win_DrawYardWindow, _UpdateYardMessage, _DrawYardData, _DrawSimKid, _Draw_SimYard, _DrawSwarm, _DrawSimColonies, _YardArea are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near DogX;
extern int near DogY;
extern int near DogFrame;
extern int near ForSaleState;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);

/* The two pool_data_fill arrays contain exact initialized bytes at the
 * measured gaps 1890-18D8 and 18E0-1918. They stand in for unclaimed
 * neighbouring objects; their identities and source declarations remain
 * unrecovered. DrawDog's five named statics retain their own target bytes. */
static int near dogObject = -1;
static unsigned char pool_data_fill_1890[72] = {0xFF, 0xFF, 0xFF, 0xFF, 0xA9, 0x00, 0x43, 0x00, 0xC0, 0x00, 0x43, 0x00, 0xB9, 0x00, 0x4A, 0x00, 0xA2, 0x00, 0x4A, 0x00, 0xA9, 0x00, 0x43, 0x00, 0xC1, 0x00, 0x43, 0x00, 0xBA, 0x00, 0x4A, 0x00, 0xA2, 0x00, 0x4A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x25, 0x73, 0x00, 0x28, 0x25, 0x64, 0x29, 0x00, 0x0A, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00};
static char near dogRunX[4] = { 3, 0, 1, 4 };
static char near dogRunY[4] = { 4, 3, 7, 2 };
static unsigned char pool_data_fill_18E0[56] = {0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x04, 0x05, 0x04, 0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x02, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x6B, 0x69, 0x64, 0x62, 0x61, 0x6C, 0x6C, 0x6F, 0x6F, 0x6E, 0x00, 0x00};
static char near dogWalkX[12] = { 1, 0, 1, 2, 0, 1, 2, 2, 2, 1, 0, 1 };
static char near dogWalkY[12] = { 0, 1, 0, 1, 2, 1, 2, 0, 0, 1, 2, 1 };

extern int far match_position;  /* scaffold reference for pool word C19E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far bHelp;  /* scaffold reference for pool word C1A0 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far mapUserButton;  /* scaffold reference for pool word C1A2 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C1A4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C1A6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C1A8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far yardUserButton;  /* scaffold reference for pool word C1AA (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far paletteFlag;  /* scaffold reference for pool word C1AC (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far activeAppFlag;  /* scaffold reference for pool word C1AE (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far captureWnd;  /* scaffold reference for pool word C1B0 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C1B2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C1B4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C1B6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C1B8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C1BA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C1BC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word C1BE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C1C0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word C1C2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapTileRect;  /* scaffold reference for pool word C1C4 (segment 9, MAPSYM_SITE_NAME) */
extern int far fileWaitFlag;  /* scaffold reference for pool word C1C6 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far MapMode;  /* scaffold reference for pool word C1C8 (segment 8, MAPSYM_SITE_NAME) */
extern int far StoreArray;  /* scaffold reference for pool word C1CA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word C1CC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatCycle;  /* scaffold reference for pool word C1CE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far custNameStrHandle;  /* scaffold reference for pool word C1D0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ncbHead;  /* scaffold reference for pool word C1D2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatDir;  /* scaffold reference for pool word C1D4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far WantRestBalloon;  /* scaffold reference for pool word C1D6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastColonyPopB;  /* scaffold reference for pool word C1D8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C1DA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C1DC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far SpidRevenge;  /* scaffold reference for pool word C1DE (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DrawYardCursor(void);
void far pool_stub_win_DrawYardWindow(void);
void far pool_stub_UpdateYardMessage(void);
void far pool_stub_DrawYardData(void);
void far pool_stub_DrawSimKid(void);
void far pool_stub_Draw_SimYard(void);
void far pool_stub_DrawSwarm(void);
void far pool_stub_DrawSimColonies(void);
void far pool_stub_YardArea(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawYardCursor)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_DrawYardWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateYardMessage)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawYardData)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSimKid)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_Draw_SimYard)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSwarm)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSimColonies)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_YardArea)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawYardCursor.
 * It only reproduces the object's selector-pool allocation order for the
 * words C19E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawYardCursor(void)
{
    volatile int t;

    t = match_position;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_DrawYardWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1A0 C1A2 C1A4 C1A6 C1A8 C1AA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_DrawYardWindow(void)
{
    volatile int t;

    t = bHelp;
    t = mapUserButton;
    t = match_length;
    t = pack_buf;
    t = Dx8;
    t = yardUserButton;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateYardMessage.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1AC C1AE C1B0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateYardMessage(void)
{
    volatile int t;

    t = paletteFlag;
    t = activeAppFlag;
    t = captureWnd;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawYardData.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1B2 C1B4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawYardData(void)
{
    volatile int t;

    t = Scycle;
    t = EditColumns;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSimKid.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1B6 C1B8 C1BA C1BC C1BE C1C0 C1C2 C1C4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSimKid(void)
{
    volatile int t;

    t = MiscStrs;
    t = LastQueenPlane;
    t = EditDragPnt;
    t = Dy8;
    t = SMode;
    t = modeButtonState;
    t = CurRestPlane;
    t = mapTileRect;
}

void far DrawDog(void)
{
    int right;
    int bottom;

    right = DogX;
    bottom = DogY;
    if (ForSaleState == 0) {
        if (DogFrame < 12) {
            right += dogWalkX[DogFrame];
            bottom += dogWalkY[DogFrame];
        } else {
            right += dogRunX[DogFrame - 12];
            bottom += dogRunY[DogFrame - 12];
        }
        if (dogObject != -1) {
            hanim_SetObjectPos(right, bottom, DogFrame + 0x2134,
                               yardAnimHandle, dogObject, -1);
        } else {
            dogObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                            DogFrame + 0x2134, -1);
        }
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _Draw_SimYard.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1C6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_Draw_SimYard(void)
{
    volatile int t;

    t = fileWaitFlag;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSwarm.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1C8 C1CA C1CC C1CE C1D0 C1D2 C1D4 C1D6 C1D8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSwarm(void)
{
    volatile int t;

    t = MapMode;
    t = StoreArray;
    t = mapCursorRect;
    t = CatCycle;
    t = custNameStrHandle;
    t = ncbHead;
    t = CatDir;
    t = WantRestBalloon;
    t = LastColonyPopB;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSimColonies.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1DA C1DC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSimColonies(void)
{
    volatile int t;

    t = Dx9;
    t = Dy9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _YardArea.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1DE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_YardArea(void)
{
    volatile int t;

    t = SpidRevenge;
}

