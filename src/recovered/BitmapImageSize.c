/* Byte-matched C reconstruction. Modern filename and isolated translation unit.
 * Historical source text and declaration spelling are not uniquely recovered. */
long BitmapImageSize(int w,int h,int planes) { return (((long)w*planes+31)/32)*h*4; }
