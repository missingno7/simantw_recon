/*
 * FindInLionList scans the lion records backwards.  The private state word
 * supplies the number of records, so the first candidate index is count-1.
 * An initially negative index returns immediately; otherwise each record is
 * selected when its two match-position bytes equal the two keys.  A miss
 * decrements the index and returns the resulting negative value when the
 * scan passes below zero.  The target's two selector loads identify the
 * shared match_position segment, whose byte fields are at -0x7f64 and
 * -0x7f44 relative to the index.
 */
extern unsigned int far LionListState[];
extern unsigned char far match_position[];

int FindInLionList(int firstKey, int secondKey)
{
    int index;

    index = LionListState[0x4544];
    --index;
    if (index < 0)
        return index;

    for (;;) {
        if (match_position[index - 0x7f64] == firstKey &&
            match_position[index - 0x7f44] == secondKey)
            return index;
        --index;
        if (index < 0)
            return index;
    }
}
