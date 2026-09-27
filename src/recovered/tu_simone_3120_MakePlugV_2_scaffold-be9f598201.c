/* Candidate translation unit simone_3120_MakePlugV_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _MakePlugV, _MakePlugH
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern unsigned char near MapA[];


void MakePlugH(int row, int column);

#pragma alloc_text(RUN2_TEXT, MakePlugH)

static unsigned char near PlugTemplateV[] = {
    107, 108, 108, 108, 109, 113, 120, 100, 120, 114, 113, 121, 116, 121, 114, 110, 111, 111, 111, 112
};
void MakePlugV(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 5; ++outer) {
        for (inner = 0; inner < 4; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner] =
                PlugTemplateV[outer + inner * 5];
    }
}

static unsigned char near PlugTemplateH[] = {
    107, 108, 108, 109, 113, 118, 119, 114, 113, 100, 100, 114, 113, 118, 119, 114, 110, 111, 111, 112
};
void MakePlugH(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 4; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner] =
                PlugTemplateH[outer + inner * 4];
    }
}

