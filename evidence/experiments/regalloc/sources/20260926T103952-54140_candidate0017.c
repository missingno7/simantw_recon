extern int near NearWords[];
int far RallocFindMem(int p, int q, int near *source) {
 unsigned char c=(unsigned char)p; int w=q; int near *np=source; int i;
 for(i=0;i<4;i++){ c=(unsigned char)(c+1); w+=np[i]; }
 return c+w+*np+i;
}
