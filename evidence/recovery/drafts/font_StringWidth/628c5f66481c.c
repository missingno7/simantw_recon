/* Count via a far-pointer walk and preserve a shared result tail. */
struct Font { unsigned char header[6]; int cellWidth; int spacing; unsigned char rest[0x22-0x0a]; int far *widths; int defaultChar; };
int far _font_StringWidth(char far *text, struct Font far *font) {
 int width, i, extra, defaultWidth, entry, result;
 width=0; i=0;
 if (font->defaultChar == 0) {
   { char far *p; int n; p=text; n=0; while(*p++) n++; result=n*font->cellWidth; }
 } else {
   extra = (font->spacing < 0) ? 1 : 0;
   if (text[0] != 0) {
     defaultWidth=(unsigned char)font->widths[font->defaultChar];
     do { entry=font->widths[(unsigned char)text[i]]; if(entry == -1) width += defaultWidth; else width += (unsigned char)entry; i++; width += extra; } while(text[i] != 0);
   }
   result=width;
 }
 return result;
}
