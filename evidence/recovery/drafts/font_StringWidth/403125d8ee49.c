/* Controlled probe: preserve the original wrapper while testing result-home elimination. */
struct Font; extern struct Font far * near curFontPtr; extern char near fontWidth;
extern int far _font_StringWidth(char far *text, struct Font far *font);
extern unsigned int strlen(const char far *text);

int far font_StringWidth(char far *text) { if (curFontPtr == 0) return (int)(strlen(text)*(int)fontWidth); return _font_StringWidth(text,curFontPtr); }
