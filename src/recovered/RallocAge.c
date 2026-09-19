/* Candidate reconstruction of the allocator age calculation. */
struct RallocAgeRecord {
    unsigned char unused[10];
    int stamp;
};

extern int far pascal GetTickCount(void);

long RallocAge(struct RallocAgeRecord far *record)
{
    return GetTickCount() - record->stamp;
}
