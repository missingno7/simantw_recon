/*
 * DoSow (SIMTWO_MODULE, unit simtwo:3EF8; same Sow* objects as _InitPillar
 * and the AddAntLion/SetAntLion members of this unit -- see
 * src/recovered/wf_tu_simtwo_3EF8_AddAntLion_2_scaffold-16d1d1e00e.c).
 *
 * Per-frame update for the three sowbug/pillbug slots (SowX/Y/Dir/Save[0..2],
 * SowTab is the direction->sprite lookup, confirmed via this packet's exact
 * MAPSYM bindings: _MapA at DGROUP+0x28e8, _LifeA at DGROUP+0x68e8, _Dx8/_Dy8
 * adjacent 8-byte far tables, _SowX/_SowY/_SowDir/_SowSave/_SowTab far
 * arrays/table). For each slot: a random chance to act at all, then a
 * further random chance to nudge its facing by -1/0/+1 (mod 8) and restamp
 * the current tile with the new facing's sprite; then compute the tile one
 * step ahead in the (possibly updated) facing. If that tile is on the map,
 * unoccupied (LifeA == 0) and clear terrain (MapA < 0x10), the sowbug moves
 * there: restore the terrain it is leaving (from SowSave), remember the
 * terrain of the tile it is entering (into SowSave), stamp that tile with
 * its facing sprite, and update its stored position.
 */

extern unsigned char near MapA[];
extern unsigned char near LifeA[128][64];
extern char far Dx8[];
extern char far Dy8[];
extern int far SRand4(void);
extern int far SRand1(int range);
extern int far IsValidA(int x, int y);

extern int far SowX[];
extern int far SowY[];
extern int far SowDir[];
extern int far SowSave[];
extern unsigned char far SowTab[];

void far DoSow(void)
{
    int i;
    int newX;
    int newY;
    int far *psy;
    int far *psx;

    for (i = 0; i < 3; i++) {
        if (SRand4() == 0)
            continue;
        if (SRand4() == 0) {
            SowDir[i] = (SowDir[i] + SRand1(3) - 1) & 7;
            MapA[SowX[i] * 64 + SowY[i]] = SowTab[SowDir[i]];
        }
        newY = Dy8[SowDir[i]] + *(psy = &SowY[i]);
        newX = Dx8[SowDir[i]] + *(psx = &SowX[i]);
        if (!IsValidA(newX, newY))
            continue;
        if (LifeA[newX][newY] != 0)
            continue;
        if (MapA[newX * 64 + newY] >= 0x10)
            continue;
        MapA[SowX[i] * 64 + SowY[i]] = SowSave[i];
        SowSave[i] = MapA[newX * 64 + newY];
        MapA[newX * 64 + newY] = SowTab[SowDir[i]];
        *psx = newX;
        *psy = newY;
    }
}
