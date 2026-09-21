/*
 * ConvertMonoMaskToTandy: given a locked mono-mask handle, allocate a new
 * mask record with the same width/height and populate it via
 * MaskMono2Tandy.  On a Tandy display (displayType == 10) the new record
 * is sized (((width*4+31)/32)*height+3)*4 bytes and tagged flag 0x84;
 * otherwise it is a half-byte-per-pixel mask sized width*height/2+12 bytes
 * and tagged flag 4.  Both allocation paths pass the debug tag
 * "tdyballoon" (confirmed from the DGROUP literal pool at both call
 * sites) and kind 1.  The type word is always 3.  MaskMono2Tandy is
 * called on the width/height sub-record (object+8) of both the new and
 * source objects.  Both handles are unlocked and the source handle is
 * freed; the new handle is returned.
 */
struct MaskObj {
    int type;
    unsigned char flag;
    unsigned char pad[5];
    int width;
    int height;
};

extern unsigned char near displayType;
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far MaskMono2Tandy(void far *dst, void far *src);

unsigned int far ConvertMonoMaskToTandy(unsigned int handle)
{
    struct MaskObj far *src;
    struct MaskObj far *dst;
    unsigned int newHandle;
    unsigned int size;

    src = (struct MaskObj far *)mem_Lock(handle);
    if (displayType == 10)
        size = (((src->width * 4 + 31) / 32) * src->height + 3) * 4;
    else
        size = src->width * src->height / 2 + 12;
    newHandle = mem_Alloc(size, 1, "tdyballoon");
    dst = (struct MaskObj far *)mem_Lock(newHandle);
    dst->width = src->width;
    dst->height = src->height;
    dst->type = 3;
    if (displayType == 10)
        dst->flag = 0x84;
    else
        dst->flag = 4;
    MaskMono2Tandy((unsigned char far *)dst + 8, (unsigned char far *)src + 8);
    mem_Unlock(handle);
    mem_Unlock(newHandle);
    mem_Free(handle);
    return newHandle;
}
