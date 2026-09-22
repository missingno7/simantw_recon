/*
 * InitPillar (SIMTWO_MODULE, unit simtwo:3EF8; neighbours _AddAntLion and
 * _SetAntLion in the same unit already use Dx8/Dy8/LionList* and the Sow*
 * far objects verbatim, per src/recovered/wf_tu_simtwo_3EF8_AddAntLion_2_
 * scaffold-16d1d1e00e.c).
 *
 * "Sow" here is short for sowbug/pillbug (the creature that rolls into a
 * "pill"/"pillar" -- see PillarX/PillarY/PillDir/PillGetLife/IsPillDead in
 * the neighbouring simtwo:4CDC unit, wf_tu_simtwo_4CDC_StorePillarMap_4_
 * scaffold-c16d27de40.c, and wf_IsPillDead / PlacePillTile).
 *
 * This clears a handful of far scalars and a small far buffer that live in
 * the same two far data segments as Dx8 and SowX/SowSave (own selector per
 * object, no exact MAPSYM name surfaced in this packet -- private-data
 * identity is expected to stay unresolved in isolation per docs/factory.md).
 * Unless a guard word is already set it then places up to two pillbugs
 * (slots 2 and 1) at random clear map tiles: pick a random (x,y) in
 * [0,128)x[0,64); if the terrain there is clear ground (< 0x10) record the
 * slot position and a random facing (0..7) into SowX/SowY/SowDir, save the
 * underlying terrain byte into SowSave so it can be restored later, and
 * stamp the map with the pillbug sprite looked up from SowTab[dir].
 */

extern unsigned char near MapA[];
extern int far SRand1(int range);

extern int far SowX[];
extern int far SowY[];
extern int far SowDir[];
extern int far SowSave[];
extern unsigned char far SowTab[];

/* Private far scalars/buffer cleared on every call; evidence-backed only by
 * segment (the first three share Dx8's far segment; the rest share the
 * SowX/SowSave far segment), not by an exact MAPSYM name. Each of the first
 * three reloads its far selector separately in the target (no shared-array
 * ES reuse), so they are three distinct objects, not one array. */
extern int far sowReset0;
extern int far sowReset1;
extern int far sowReset2;
extern int far sowResetB;
extern int far sowResetC;
extern int far sowResetD[6];
extern int far sowGuard;

void far InitPillar(void)
{
    int i;
    int x;
    unsigned char near *p;
    int y;

    sowReset0 = 0;
    sowReset1 = 0;
    sowReset2 = 0;
    sowResetB = 0;
    sowResetC = 0;
    for (i = 0; i < 6; i++)
        sowResetD[i] = 0;

    if (sowGuard != 0)
        return;

    for (i = 2; i != 0; i--) {
        x = SRand1(0x80);
        y = SRand1(0x40);
        if (*(p = &MapA[y + x * 64]) < 0x10) {
            SowX[i] = x;
            SowY[i] = y;
            SowDir[i] = SRand1(8);
            SowSave[i] = *p;
            *p = SowTab[SowDir[i]];
        }
    }
}
