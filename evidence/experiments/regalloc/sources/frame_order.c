int far RallocFindMem(int p) {
 volatile char c=(char)p; volatile int a=p+1; volatile char d=(char)(p+2); volatile long wide=(long)p+3; volatile int b=p+4;
 a+=1; b+=2; wide+=3L; c+=1; d+=2; return (int)(a+b+wide+c+d);
}
