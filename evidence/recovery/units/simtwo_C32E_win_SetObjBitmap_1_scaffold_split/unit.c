/* Candidate translation unit simtwo_C32E_win_SetObjBitmap_1_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_SetObjBitmap
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

struct WinObject {
    unsigned char reserved[0x21];
    unsigned char type;
    unsigned char pad[6];
    int bitmap;
};
struct WinBucket {
    unsigned char header[0xc];
    int count;
    unsigned char rest[0x2c - 0xe];
    struct WinObject far *objects[256];
};
extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far Punt(char far *message, ...);


void far pool_literal_fill_BD3C(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_literal_fill_BD3C)

/* SCAFFOLD, not recovered source: body literals between _win_SetObjBitmap and _win_SetObjBitmap (DGROUP BD3C-BDDA), unclaimed members' body literals. */
void far pool_literal_fill_BD3C(void)
{
    volatile char far *p;

    p = "\103\101\116\116\117\124\040\114\117\101\104\040\127\111\116\104\117\127\040\045\060\063\170\000\000\200\000\200\000\200\000\200\103\141\156\156\157\164\040\154\157\141\144\040\162\145\163\157\165\162\143\145\012\160\154\145\141\163\145\040\164\162\171\040\141\156\157\164\150\145\162\000\107\145\156\145\162\151\143\040\127\151\156\144\157\167\000\107\145\156\145\162\151\143\127\151\156\144\157\167\000\111\116\104\105\130\000\046\103\154\157\163\145\011\103\164\162\154\053\106\064\000\116\145\170\046\164\011\103\164\162\154\053\106\066\000\111\116\104\105\130\000\146\157\162\155\141\164\123\164\162\000\111\116\104\105\130";
}

void far win_SetObjBitmap(int objectNumber, int bitmap)
{
    struct WinObject far *object;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    if ((unsigned char)objectNumber >= bucket->count)
        Punt("Attempt to get obj address outsize window");
    object = bucket->objects[(unsigned char)objectNumber];
    if (object->type != 6)
        Punt("Attempt to set bitmap on non-bitmap object");
    object->bitmap = bitmap;
    win_UnlockWin(objectNumber);
}

