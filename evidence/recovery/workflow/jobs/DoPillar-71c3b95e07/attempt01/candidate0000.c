/*
 * Probe candidate: only the pillar-creation prologue of DoPillar is
 * implemented, to check whether a standalone compile of this unit's
 * first-use function reproduces the original's DGROUP-selector-word
 * ES-load mechanism (mov es, word ptr [ADDR]) for TERRAINset/Dx8/
 * PillarSeg/PillDir, versus the CONST-immediate-fixup mechanism seen in
 * a standalone MakePillFood compile. Not a candidate for acceptance.
 */
extern int far TERRAINset;
extern int far Dx8;
extern int far PillarSeg;
extern int far PillDir;
extern void far DoSow(void);
extern void far MakeAPill(void);

void far DoPillar(void)
{
    if (TERRAINset == 1)
        return;
    DoSow();
    if (Dx8 == 0) {
        MakeAPill();
        Dx8 = 1;
        PillarSeg = 4;
        return;
    }
    if (PillDir == 0) {
        return;
    }
}
