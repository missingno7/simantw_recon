int far RallocFindMem(int p) {
 int total=p, i; volatile int outer=p+3; volatile int row, col;
 for(i=0;i<2;i++){ row=i+1; col=i+2; total+=row+col; }
 return total+outer+i;
}
