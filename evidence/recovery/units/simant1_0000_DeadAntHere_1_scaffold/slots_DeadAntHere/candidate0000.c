/*
 * DeadAntHere: place/age a dead-ant corpse marker on the A-plane map at
 * (x, y) for a colony flagged by type, recycling one slot of a 100-entry
 * circular buffer (match_position[0x4f54], DeadX/DeadY) that remembers
 * the last 100 corpse positions. The previous occupant of the recycled
 * slot is aged or restored first: when TERRAINset (PACK:9B6E, see
 * src/recovered/wf_IsItFood-c02f58780a.c) is clear, an old corpse tile in
 * the plain 0x10-0x17 band is replaced by a fresh random background tile
 * (SRand16); when set, an old tile in the 8-0x17 band is stepped toward
 * its decayed sub-band. The new cell then gets a fresh corpse tile: with
 * TERRAINset clear, any free cell (< 0x18) is stamped with SRand4() plus
 * 0x14 (type != 0) or 0x10 (type == 0), unconditionally; with TERRAINset
 * set, only a cell whose current value is still a fresh state (< 4) is
 * restamped, combining that state, a coin flip (SRand1(2)) and type.
 * LifeA is always cleared for the new cell. MapA/LifeA reuse
 * src/recovered/wf_GetMap-cddf28f960.c and
 * src/recovered/wf_GetLife-172de0cfc1.c; match_position reuses
 * src/recovered/wf_GetAntIndex-a8eba5e594.c.
 */
extern int far match_position;
extern unsigned char far DeadX[];
extern unsigned char far DeadY[];
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern int far SRand1(int range);
extern int far SRand4(void);
extern int far SRand16(void);

void far DeadAntHere(int x, int y, int type)
{
    int far *slot;
    int ox, oy, otile;
    int tile;
    int state;

    slot = &match_position + 0x4f54;
    *slot = *slot + 1;
    if (*slot >= 100)
        *slot = 0;

    oy = DeadY[*slot];
    ox = DeadX[*slot];
    otile = MapA[ox * 64 + oy];

    if (TERRAINset == 0) {
        if (otile >= 0x10 && otile < 0x18)
            MapA[ox * 64 + oy] = (unsigned char)SRand16();
        DeadX[*slot] = (unsigned char)x;
        DeadY[*slot] = (unsigned char)y;
        tile = x * 64 + y;
        if (MapA[tile] < 0x18) {
            if (type != 0)
                MapA[tile] = (unsigned char)(SRand4() + 0x14);
            else
                MapA[tile] = (unsigned char)(SRand4() + 0x10);
        }
    } else {
        if (otile >= 8 && otile < 0x18)
            MapA[ox * 64 + oy] = (unsigned char)((otile - 8) >> 2);
        DeadX[*slot] = (unsigned char)x;
        DeadY[*slot] = (unsigned char)y;
        tile = x * 64 + y;
        state = MapA[tile];
        if (state < 4) {
            if (type != 0)
                MapA[tile] = (unsigned char)(SRand1(2) + state * 4 + 0xa);
            else
                MapA[tile] = (unsigned char)(SRand1(2) + (state + 2) * 4);
        }
    }
    LifeA[tile] = 0;
}
