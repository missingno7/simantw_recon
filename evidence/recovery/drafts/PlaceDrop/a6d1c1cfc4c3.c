/* PlaceDrop: keep the map pointer and half-map index in a typed local record. */
extern unsigned char near MapA[];
extern unsigned char far Dx8[];
extern unsigned char far RxTab[];
extern unsigned char far RyTab[];
extern int far RRand(int range);
struct PlaceDropLocals { int idx; unsigned char near *p; };
void far PlaceDrop(int i)
{
    int x; int y;
    struct PlaceDropLocals local;
    x=RRand(128); y=RRand(64);
    RxTab[i]=x; RyTab[i]=y;
    local.p=&MapA[(x<<6)+y];
    if (*local.p<0xe) {
        *local.p=0x74;
        local.idx=((x>>1)<<5)+(y>>1);
        Dx8[local.idx+0x52d2]=0; Dx8[local.idx+0x5ad2]=0;
        if (Dx8[local.idx+0x62d2]>=0x14) Dx8[local.idx+0x62d2]-=0x14;
        else Dx8[local.idx+0x62d2]=0;
        Dx8[local.idx+0x6ad2]=0;
        if (Dx8[local.idx+0x72d2]>=0x14) Dx8[local.idx+0x72d2]-=0x14;
        else Dx8[local.idx+0x72d2]=0;
        Dx8[local.idx+0x7ad2]=0;
    }
}
