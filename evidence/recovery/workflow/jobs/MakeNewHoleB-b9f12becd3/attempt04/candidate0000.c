/*
 * MakeNewHoleB(x): black-colony surface-hole placement. Rolls roll=SRand1(31)
 * once, then picks a search algorithm by TERRAINset. When TERRAINset != 0 it
 * scans up to 0x22 rings r = (roll + j) % 0x20 + 2 reading MapA[r][x] and
 * applying the same code-to-hole-marker table as the admitted CanBeHouseHole
 * (0 -> 0x86; 2/3 -> 0x8a; 0x5e..0x61 -> value+0x22; 0x66 -> 0x85; 0x68 ->
 * 0x84; anything else -> 0/not found), breaking on the first nonzero hole
 * code; when found it writes MapA[r][x] and records the position in
 * LastNewHoleB[2]/LastNewExitB[2]. When TERRAINset == 0 it instead scans the
 * same ring sequence calling IsClear3x3(1, r, x), and on the first clear
 * ring marks MapA[r][x] = 0x50, records the same two position pairs, and
 * stamps the eight Dx8/Dy8 neighbours of (r, x) into MapA with the private
 * per-direction HoleValues[] table wherever the neighbour is in bounds and
 * not already >= 0x50 (mirrors the admitted-but-blocked HoleBorder draft,
 * which references the same private near array at DGROUP:230C). A ring
 * search that exhausts all 0x22 rings without success returns without
 * touching HoleMapB or digging. On success both branches converge on the
 * shared tail: HoleMapB[x] = (unsigned char)r; DigTileB(x, 1). Declarations
 * for MapA/HoleMapB/Dx8/Dy8/DigTileB/SRand1 are reused verbatim from the
 * RandWorld/DigOutBNest translation unit
 * (src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c) and the
 * admitted CanBeHouseHole (src/recovered/wf_CanBeHouseHole-987878d5ee.c,
 * same unit simone:16AE, whose lookup table this function duplicates
 * inline rather than calling); _LastNewHoleB/_LastNewExitB are exact MAPSYM
 * names (evidence/symbols/symbols.csv, SIMANT_DATA_GROUP 33626/33618, each
 * a 4-byte/2-word object) and HoleValues is the private near array name
 * hypothesised by the HoleBorder draft that shares this same DGROUP:230C
 * reference (evidence/recovery/workflow/jobs/HoleBorder-fbe467816d/candidate.c,
 * layout/private-data-topology.json).
 */
extern unsigned char near MapA[128][64];
extern unsigned char far HoleMapB[];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near HoleValues[];
extern int far TERRAINset;
extern int far LastNewHoleB[2];
extern int far LastNewExitB[2];

extern int far SRand1(int range);
extern int far IsClear3x3(int kind, int row, int col);
extern void far DigTileB(int x, int y);

void far MakeNewHoleB(int x)
{
    int hole;
    int j;
    int roll;
    int r;
    int v;
    int k;
    int newRow;
    int newCol;

    roll = SRand1(0x1f);

    if (TERRAINset != 0) {
        for (j = 0; j < 0x22; j++) {
            r = (roll + j) % 0x20 + 2;
            v = MapA[r][x];
            if (v == 0)
                hole = 0x86;
            else if (v == 2)
                hole = 0x8a;
            else if (v == 3)
                hole = 0x8a;
            else if (v >= 0x5e) {
                if (v < 0x62)
                    hole = v + 0x22;
                else if (v == 0x66)
                    hole = 0x85;
                else if (v == 0x68)
                    hole = 0x84;
                else
                    hole = 0;
            } else
                hole = 0;
            if (hole != 0)
                break;
        }
        if (hole != 0) {
            MapA[r][x] = (unsigned char)hole;
            LastNewHoleB[0] = r;
            LastNewHoleB[1] = x;
            LastNewExitB[0] = x;
            LastNewExitB[1] = 0;
        }
        if (j == 0x22)
            return;
        goto tail;
    }

    for (j = 0; j < 0x22; j++) {
        r = (roll + j) % 0x20 + 2;
        if (IsClear3x3(1, r, x))
            break;
    }
    if (j == 0x22)
        return;

    MapA[r][x] = 0x50;
    LastNewHoleB[0] = r;
    LastNewHoleB[1] = x;
    LastNewExitB[0] = x;
    LastNewExitB[1] = 0;

    for (k = 0; k < 8; k++) {
        newRow = Dx8[k] + r;
        newCol = Dy8[k] + x;
        if (newRow < 0 || newRow > 0x7f || newCol < 0 || newCol > 0x3f)
            continue;
        if (MapA[newRow][newCol] >= 0x50)
            continue;
        MapA[newRow][newCol] = HoleValues[k];
    }

tail:
    HoleMapB[x] = (unsigned char)r;
    DigTileB(x, 1);
}
