extern int __based(__segname("PACK")) Dx8[];
extern int far ConvColor(int); extern void far win_FillObjRect(int,int); extern void near drawHistGraph(int,int,int);
void far win_DrawHistoryWindow(int flags) {
    register int index; register int __based(__segname("PACK")) *sample; int value; int *valueRef = &value;
    if((flags & 2)==0) return;
    win_FillObjRect(0x150e,ConvColor(0));
    sample=&Dx8[0x472a]; index=0;
    while(sample < &Dx8[0x472e]) {
        value=sample[index];
        if(*valueRef!=(int)0x8000) drawHistGraph(*valueRef,0,index);
        ++index; ++sample;
    }
}
