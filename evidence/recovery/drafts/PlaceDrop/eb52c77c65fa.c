/* PlaceDrop: retain the branch-local scent index in an automatic home. */
extern unsigned char near MapA[];
extern unsigned char far Dx8[];
extern unsigned char far RxTab[];
extern unsigned char far RyTab[];
extern int far RRand(int range);
void far PlaceDrop(int i)
{
    int x; int y; unsigned char near *p;
    volatile int idx;
    x=RRand(128); y=RRand(64); RxTab[i]=x; RyTab[i]=y;
    p=&MapA[(x<<6)+y];
    if (*p<0xe) {
        *p=0x74;
        idx=((x>>1)<<5)+(y>>1);
        Dx8[idx+0x52d2]=0; Dx8[idx+0x5ad2]=0;
        if (Dx8[idx+0x62d2]>=0x14) Dx8[idx+0x62d2]-=0x14;
        else Dx8[idx+0x62d2]=0;
        Dx8[idx+0x6ad2]=0;
        if (Dx8[idx+0x72d2]>=0x14) Dx8[idx+0x72d2]-=0x14;
        else Dx8[idx+0x72d2]=0;
        Dx8[idx+0x7ad2]=0;
    }
}
