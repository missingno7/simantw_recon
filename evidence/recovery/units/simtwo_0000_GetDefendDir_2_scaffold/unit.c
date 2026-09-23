/* Candidate translation unit simtwo_0000_GetDefendDir_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GetDefendDir, _GetRedDefendDir
 * SCAFFOLDED: unclaimed members _GetStrategy, _SetCasteProd, _SetModeProd, _GstrR, _StartAttack, _Recruit, _UnRecruit, _GetNewMode, _GetForageDir, _GetNestDir are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near MePlane;
extern int near SpidX;
extern int near SpidY;
extern int far ChaseSpid;
extern int far FuzLocX;
extern int far FuzLocY;
extern int far ModePopB[];
extern char far TurnTab[][8];
extern int far SRand1(unsigned int range);
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far GetNestDir(int x, int y, int dir, int flag);
extern int far RedPlane;
extern int far RedLocX;
extern int far RedLocY;
extern int far ModePopR[];

extern int far match_position;  /* scaffold reference for pool word C4C4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C4C6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C4C8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C4CA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C4CC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C4CE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C4D0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ListIndexA;  /* scaffold reference for pool word C4D2 (segment 9, MAPSYM_SITE_NAME) */
extern int far Scycle;  /* scaffold reference for pool word C4D4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C4D6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C4D8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far relSearchDirs;  /* scaffold reference for pool word C4DA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far absSearchDirs;  /* scaffold reference for pool word C4DC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far IsCarryCaste;  /* scaffold reference for pool word C4DE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far ModeAuto;  /* scaffold reference for pool word C4E0 (segment 9, MAPSYM_SITE_NAME) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C4E2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far UnCarryCaste;  /* scaffold reference for pool word C4E4 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far YMapPopB;  /* scaffold reference for pool word C4E8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far YMapPopR;  /* scaffold reference for pool word C4EA (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_GetStrategy(void);
void far pool_stub_SetCasteProd(void);
void far pool_stub_SetModeProd(void);
void far pool_stub_GstrR(void);
void far pool_stub_StartAttack(void);
void far pool_stub_Recruit(void);
void far pool_stub_UnRecruit(void);
void far pool_stub_GetNewMode(void);
void far pool_stub_GetForageDir(void);
void far pool_stub_GetNestDir(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetStrategy)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetCasteProd)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetModeProd)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GstrR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_StartAttack)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_Recruit)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UnRecruit)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetNewMode)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetForageDir)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetNestDir)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetStrategy.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4BE C4C0 C4C2 C4C4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetStrategy(void)
{
    volatile int t;

    t = (int)ChaseSpid;
    t = (int)FuzLocX;
    t = (int)FuzLocY;
    t = match_position;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetCasteProd.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4C6 C4C8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetCasteProd(void)
{
    volatile int t;

    t = Dx8;
    t = Dy8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetModeProd.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4CA C4CC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetModeProd(void)
{
    volatile int t;

    t = Dx9;
    t = Dy9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GstrR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4CE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GstrR(void)
{
    volatile int t;

    t = match_length;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _StartAttack.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4D0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_StartAttack(void)
{
    volatile int t;

    t = pack_buf;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _Recruit.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4D2 C4D4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_Recruit(void)
{
    volatile int t;

    t = ListIndexA;
    t = Scycle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UnRecruit.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4D6 C4D8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UnRecruit(void)
{
    volatile int t;

    t = EditColumns;
    t = MiscStrs;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetNewMode.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4DA C4DC C4DE C4E0 C4E2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetNewMode(void)
{
    volatile int t;

    t = relSearchDirs;
    t = absSearchDirs;
    t = IsCarryCaste;
    t = ModeAuto;
    t = LastQueenPlane;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetForageDir.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4E4 C4E6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetForageDir(void)
{
    volatile int t;

    t = UnCarryCaste;
    t = TurnTab[0][0];
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetNestDir.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4E8 C4EA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetNestDir(void)
{
    volatile int t;

    t = YMapPopB;
    t = YMapPopR;
}

int far GetDefendDir(int x, int y, int dir)
{
    int r;

    if (x == 0) {
        if (y == 0)
            r = SRand1(3) + 3;
        else if (y == 63)
            r = SRand1(3) + 1;
        else
            r = SRand1(5) + 1;
    } else if (y == 0) {
        if (x == 127)
            r = SRand1(3) + 5;
        else
            r = SRand1(5) + 3;
    } else if (x == 127) {
        if (y == 63)
            r = SRand1(3) + 7;
        else
            r = SRand1(5) + 5;
    } else if (y == 63)
        r = SRand1(5) + 7;
    else
        r = 0;

    if (r != 0)
        return (unsigned char)r - 1 & 7;

    switch (MePlane) {
    case 1:
        goto chase;
    case 2:
        return GetNestDir(x, y, dir, 0);
    case 3:
        return GetNestDir(x, y, dir, 0x80);
    }
check:
    if (r != 0)
        return ((char far *)TurnTab - 1)[dir * 8 + r];
    return dir;

chase:
    if (ChaseSpid == 1) {
        r = GetDir(x, y, SpidX >> 4, SpidY >> 4);
    } else {
        r = GetDis(x, y, FuzLocX, FuzLocY);
        if (ModePopB[5] >> 1 < r)
            r = GetDir(x, y, FuzLocX, FuzLocY);
        else
            r = SRand1(8) + 1;
    }
    goto check;
}

int far GetRedDefendDir(int x, int y, int dir)
{
    int r;

    if (x == 0) {
        if (y == 0)
            r = SRand1(3) + 3;
        else if (y == 63)
            r = SRand1(3) + 1;
        else
            r = SRand1(5) + 1;
    } else if (y == 0) {
        if (x == 127)
            r = SRand1(3) + 5;
        else
            r = SRand1(5) + 3;
    } else if (x == 127) {
        if (y == 63)
            r = SRand1(3) + 7;
        else
            r = SRand1(5) + 5;
    } else if (y == 63)
        r = SRand1(5) + 7;
    else
        r = 0;

    if (r != 0)
        return (unsigned char)r - 1 & 7;

    switch (RedPlane) {
    case 1:
        goto chase;
    case 2:
        return GetNestDir(x, y, dir, 0);
    case 3:
        return GetNestDir(x, y, dir, 0x80);
    }
check:
    if (r != 0)
        return ((char far *)TurnTab - 1)[dir * 8 + r];
    return dir;

chase:
    r = GetDis(x, y, RedLocX, RedLocY);
    if (ModePopR[5] >> 1 < r)
        r = GetDir(x, y, RedLocX, RedLocY);
    else
        r = SRand1(8) + 1;
    goto check;
}

