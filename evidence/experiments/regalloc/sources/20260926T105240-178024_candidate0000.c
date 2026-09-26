int far SimQueenR(int p) {
 int total=p, i; volatile int outer=p+3;
 for(i=0;i<2;i++){ volatile int row=i+1; volatile int col=i+2; total+=row+col; }
 return total+outer+i;
}
