/* The yard message public owns the native handle, two count-and-table regions,
 * the sixteen-entry information index, and the fixed-stride named info records.
 * Style rows are ten bytes; info-name rows are 34 bytes. */
struct YardStyleRow {
    unsigned char style;
    unsigned char flags;
    unsigned char reserved[8];
};

struct YardInfoName {
    unsigned char id;
    unsigned char flags;
    char name[32];
};

struct YardMessageData {
    int handle;
    unsigned char reservedBeforeStyles[648];
    unsigned int styleCount;
    struct YardStyleRow styleRows[64];
    unsigned int infoCount;
    unsigned int infoIndex[16];
    unsigned int selectedInfo;
    struct YardInfoName names[27];
    unsigned char trailing[4];
};

int __based(__segname("SIMANT_DATA_GROUP")) yardBalloon = 0;
int __based(__segname("SIMANT_DATA_GROUP")) yardMsgBuf = 0;
int __based(__segname("SIMANT_DATA_GROUP")) yardBalloonHandle = -1;

struct YardMessageData __based(__segname("SIMANT_DATA_GROUP")) yardMsgHandle = {
    -1,
    {0},
    0,
    {{0}},
    0,
    {0},
    0,
    {
        {0x80, 0, "HIGHLIGHTED"},
        {0x85, 3, "CHITIN"},
        {0x8e, 3, "MAXILLAE"},
        {0x8f, 3, "OCELLI"},
        {0x90, 3, "INFRABUCCAL"},
        {0x91, 3, "CROP"},
        {0x92, 3, "MIDGUT"},
        {0x93, 3, "TROPHALLAXIS"},
        {0x94, 3, "CASTE"},
        {0x95, 3, "LARVAE"},
        {0x96, 3, "PUPATE"},
        {0x97, 3, "CASTES"},
        {0x98, 3, "PUPAE"},
        {0x99, 3, "ECLOSE"},
        {0x9a, 3, "CALLOWS"},
        {0x9b, 3, "PHEROMONES"},
        {0x9c, 3, "BROOD"},
        {0x9d, 3, "HONEYDEW"},
        {0x9e, 3, "APHIDS"},
        {0x9f, 3, "BREEDERS"},
        {0xa0, 3, "RECRUIT"},
        {0xa1, 3, "FORAGE"},
        {0xc3, 3, "FORAGING"},
        {0xc4, 3, "QUEENCHAMBER"},
        {0xc5, 3, "NURSERIES"},
        {0xc6, 3, "EGGS"},
        {0xc7, 3, "NOP"}
    },
    {0}
};
