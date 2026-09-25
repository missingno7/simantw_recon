/*
 * Edit-buffer invalidation state: header words, pointers to the three named
 * health fields, character/mask words, and the zeroed backing workspace.
 */
extern int __based(__segname("DGROUP")) MeHealth;
extern int __based(__segname("DGROUP")) HealthB;
extern int __based(__segname("DGROUP")) HealthR;

struct EditInvalidState {
    int invalidFlag;
    unsigned int sentinel;
    unsigned int slotValues[3];
    int far *healthFields[3];
    unsigned char reservedBeforeCodes[64];
    unsigned int codes[4];
    unsigned int masks[4];
    unsigned int maskCount;
    unsigned char reservedWorkspace[1330];
};

struct EditInvalidState __based(__segname("SIMANT_DATA_GROUP")) editBufInvalidFlag = {
    0,
    0xffff,
    { 0x11, 0x12, 0x13 },
    { &MeHealth, &HealthB, &HealthR },
    { 0 },
    { 'C', 'F', 'I', 'E' },
    { 0x8000, 0x8000, 0x8000, 0x8000 },
    0x000f,
    { 0 }
};
