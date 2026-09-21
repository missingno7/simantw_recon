/*
 * FindIndex: binary-search index idx's sorted record array (stride 8:
 * pad[4], int value @+4, byte caste @+6) for an exact (value, caste)
 * match, ordered primarily by caste then by value (both ascending).  The
 * search narrows to the leftmost position not less than the key (a
 * standard lower-bound binary search: a record that is greater, or equal
 * with caste matching, moves high down; anything less moves low up), then
 * checks whether the record at that position is an exact match.  low and
 * the last-probed record pointer are both private static scratch (reset
 * at entry), matching the two unnamed DGROUP words this routine writes on
 * every probe.  Returns a far pointer to the matching record, or NULL.
 */
struct IndexRec {
    unsigned char pad[4];
    int value;
    unsigned char caste;
    unsigned char pad2;
};

extern int far match_position[];
#define AT(off) (mp[off])

static int lowPos = 0;
static struct IndexRec far *probe = 0;

void far *FindIndex(int idx, int value, unsigned char caste)
{
    unsigned char far *mp;
    int recBase;
    int high;
    int maxIndex;
    int mid;

    mp = (unsigned char far *)match_position;
    lowPos = 0;
    recBase = idx * 0x7c;
    high = *(int far *)&AT(recBase + 0x745c) - 1;
    maxIndex = high;
    if (high >= 0) {
        do {
            mid = (lowPos + high) / 2;
            probe = (struct IndexRec far *)(*(unsigned char far * far *)&AT(recBase + 0x7458) + mid * 8);
            if (probe->caste > caste || (probe->caste == caste && probe->value >= value))
                high = mid - 1;
            else
                lowPos = mid + 1;
        } while (lowPos <= high);
    }
    if (lowPos > maxIndex)
        return 0;
    probe = (struct IndexRec far *)(*(unsigned char far * far *)&AT(recBase + 0x7458) + lowPos * 8);
    if (probe->value != value)
        return 0;
    if (probe->caste != caste)
        return 0;
    return probe;
}
