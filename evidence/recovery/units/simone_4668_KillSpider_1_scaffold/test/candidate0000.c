/* Candidate translation unit simone_4668_KillSpider_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _KillSpider
 * SCAFFOLDED: unclaimed members _InitSpider, _MoveSpider are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int SMode[];
extern int DeathCnt[];
extern int Scycle[];

extern int far SpidBurpCnt;  /* scaffold reference for pool word C436 (segment 9, MAPSYM_SITE_NAME) */
extern int far EatCnt;  /* scaffold reference for pool word C438 (segment 9, MAPSYM_SITE_NAME) */
extern int far SCorpseBase;  /* scaffold reference for pool word C43A (segment 9, MAPSYM_SITE_NAME) */
extern int far Scycle2;  /* scaffold reference for pool word C43E (segment 9, MAPSYM_SITE_NAME) */
extern int far SpidRevenge;  /* scaffold reference for pool word C440 (segment 9, MAPSYM_SITE_NAME) */
extern int far RevSpider;  /* scaffold reference for pool word C442 (segment 8, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word C444 (segment 9, MAPSYM_SITE_NAME) */
extern int far SpidOn;  /* scaffold reference for pool word C446 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeSMode;  /* scaffold reference for pool word C44A (segment 9, MAPSYM_SITE_NAME) */
extern int far Starg;  /* scaffold reference for pool word C44C (segment 9, MAPSYM_SITE_NAME) */
extern int far StargLife;  /* scaffold reference for pool word C44E (segment 9, MAPSYM_SITE_NAME) */
extern int far SuserX;  /* scaffold reference for pool word C450 (segment 9, MAPSYM_SITE_NAME) */
extern int far SuserY;  /* scaffold reference for pool word C452 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeMode;  /* scaffold reference for pool word C454 (segment 9, MAPSYM_SITE_NAME) */
extern int far AlistT;  /* scaffold reference for pool word C456 (segment 8, MAPSYM_SITE_NAME) */

void far pool_stub_InitSpider(void);
void far pool_stub_MoveSpider(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitSpider)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_MoveSpider)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitSpider.
 * It only reproduces the object's selector-pool allocation order for the
 * words C436 C438 C43A C43C C43E C440 C442 C444 C446 C448 C44A C44C C44E C450 C452; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitSpider(void)
{
    volatile int t;

    t = SpidBurpCnt;
    t = EatCnt;
    t = SCorpseBase;
    t = Scycle[0];
    t = Scycle2;
    t = SpidRevenge;
    t = RevSpider;
    t = CurGameType;
    t = SpidOn;
    t = SMode[0];
    t = MeSMode;
    t = Starg;
    t = StargLife;
    t = SuserX;
    t = SuserY;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _MoveSpider.
 * It only reproduces the object's selector-pool allocation order for the
 * words C454 C456 C458; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_MoveSpider(void)
{
    volatile int t;

    t = MeMode;
    t = AlistT;
    t = DeathCnt[0];
}

void KillSpider(void)
{
    SMode[0] = 5;
    DeathCnt[0] = 500;
    Scycle[0] = 0;
}

