from pathlib import Path
import hashlib, json
base=Path('evidence/recovery/units/simant1_75F4_DoAntSimY_3_scaffold/unit.c').read_text(encoding='latin1')
initial=Path('evidence/recovery/workflow/jobs/GetMyInitialRandDir-72875fbed4/attempt07/candidate0000.c').read_text(encoding='latin1')
assert base.endswith('\n')
assert 'int far CheckMyBestDirs(' in base and 'void far pool_stub_DoAntMoveY(' in base
assert 'void far GetMyInitialRandDir(' in initial
insert='''

/* DIAGNOSTIC ONLY: unclaimed selector stand-ins after the exact prior unit.
 * Their references use representative publics verified in MAPSYM segment 8.
 * These helper bodies are POOLSTUB_TEXT only and are never claimed as source. */
extern int far TurnTab;       /* representative MAPSYM public, segment 8 */
extern int far relSearchDirs; /* representative MAPSYM public, segment 8 */
extern int far absSearchDirs; /* representative MAPSYM public, segment 8 */
extern int far IsCarryCaste;  /* representative MAPSYM public, segment 8 */
extern int far UnCarryCaste;  /* representative MAPSYM public, segment 8 */
extern int far YMapPopB;      /* representative MAPSYM public, segment 8 */
extern int far YMapPopR;      /* representative MAPSYM public, segment 8 */
extern int far Scycle;        /* representative MAPSYM public, segment 9 */
void far pool_stub_ExitNest(void);
void far pool_stub_ZeroGap(void);
void far pool_stub_GetMyDis(void);
void far pool_stub_GetMyNextRandDirs(void);
int far GetMyInitialRandDir(int unused1, int unused2, int unused3,
                            int unused4, int count, int a, int b,
                            int c, int d);
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ExitNest)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ZeroGap)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetMyDis)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetMyNextRandDirs)
#pragma alloc_text(RUN4_TEXT, GetMyInitialRandDir)

/* SCAFFOLD ONLY: stand-in for three unclaimed segment-8 selectors at C3E2-E6. */
void far pool_stub_ExitNest(void)
{
    volatile int t;
    t = TurnTab;
    t = relSearchDirs;
    t = absSearchDirs;
}

/* SCAFFOLD ONLY: measured three-scalar, six-byte unrelocated CONST gap C3E8-ED.
 * This filler has no asserted historical owner and is not a recovered object. */
static const __segment near scaffoldZero0 = 0;
static const __segment near scaffoldZero1 = 0;
static const __segment near scaffoldZero2 = 0;
void far pool_stub_ZeroGap(void)
{
    volatile int t;
    t = scaffoldZero0;
    t = scaffoldZero1;
    t = scaffoldZero2;
}

/* SCAFFOLD ONLY: stand-in for four unclaimed segment-8 selectors at C3EE-F4. */
void far pool_stub_GetMyDis(void)
{
    volatile int t;
    t = IsCarryCaste;
    t = UnCarryCaste;
    t = YMapPopB;
    t = YMapPopR;
}

/* SCAFFOLD ONLY: stand-in for the unclaimed segment-9 selector at C3F6. */
void far pool_stub_GetMyNextRandDirs(void)
{
    volatile int t;
    t = Scycle;
}

'''
# preserve the exact candidate text; put its definition after the stubs, under RUN4_TEXT.
out=Path('evidence/experiments/simant1-selector-zero-gap-20260924/unit-diagnostic-GetMyInitial.c')
out.write_text(base+insert+initial,encoding='latin1')
print(json.dumps({'path':str(out),'size':out.stat().st_size,'sha256':hashlib.sha256(out.read_bytes()).hexdigest(),'base_sha256':hashlib.sha256(base.encode('latin1')).hexdigest(),'attempt07_sha256':hashlib.sha256(initial.encode('latin1')).hexdigest()},indent=2))