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

/* The clear sequence addresses the named SIMANT_DATA_GROUP words
 * PillarState/PillarX/PillarY, then the PACK objects PillarSeg, PillDir,
 * PillarMap[0..5], and TERRAINset. */
extern int far PillarState;
extern int far PillarX;
extern int far PillarY;
extern int far PillarSeg;
extern int far PillDir;
extern int far PillarMap[6];
extern int far TERRAINset;

void far InitPillar(void)
{
    int i;
    int x;
    int y;


    PillarState = 0;
    PillarX = 0;
    PillarY = 0;
    PillarSeg = 0;
    PillDir = 0;
    for (i = 0; i < 6; i++)
        PillarMap[i] = 0;

    if (TERRAINset != 0)
        return;

    i = 2;
    while (i) {
        x = SRand1(0x80);
        y = SRand1(0x40);
        if (MapA[x * 64 + y] < 0x10) {
            SowX[i] = x;
            SowY[i] = y;
            SowDir[i] = SRand1(8);
            SowSave[i] = MapA[x * 64 + y];
            MapA[x * 64 + y] = SowTab[SowDir[i]];
            --i;
        }
    }
}
