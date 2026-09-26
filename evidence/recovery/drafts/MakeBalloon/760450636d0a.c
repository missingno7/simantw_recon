/*
 * Hypothesis: split escaped newline markers, measure each line, create a
 * locked bitmap large enough for the longest line, render the text, then
 * convert the monochrome mask for the active display class.
 */
extern unsigned char near displayType;
extern unsigned int strlen(const char far *text);
extern void far *_fmemcpy(void far *dst, const void far *src, unsigned int count);
extern int font_StringWidth(char far *string);
extern unsigned int mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int mem_Unlock(unsigned int handle);
extern void far *malloc(unsigned int size);
extern void far free(void far *block);
extern void Punt(char far *message, ...);
extern void far font_MakeImage(char far *text, int mode, void far *font);
extern void ConvertMonoMaskToColor(unsigned int handle);
extern void ConvertMonoMaskToTandy(unsigned int handle);

unsigned int far MakeBalloon(char far *text, int mode)
{
    char far *copy;
    char far *lines[10];
    unsigned int handle;
    unsigned char far *image;
    unsigned long bytes;
    int width;
    int widest;
    int lineCount;
    int i;
    unsigned int textLength;

    copy = (char far *)malloc(0x12c);
    if (copy == 0) {
        Punt("Cannot allocate balloon text", 0);
        return 0;
    }

    textLength = strlen(text);
    if (textLength > 0x12b)
        textLength = 0x12b;
    _fmemcpy(copy, text, textLength);
    copy[textLength] = 0;

    widest = 0;
    lineCount = 0;
    lines[lineCount++] = copy;
    for (i = 0; copy[i] != 0; ++i) {
        if (copy[i] == '\\' && copy[i + 1] == 'n') {
            copy[i] = 0;
            copy[i + 1] = 0;
            lines[lineCount++] = copy + i + 2;
        }
    }
    for (i = 0; i < lineCount; ++i) {
        width = font_StringWidth(lines[i]);
        if (width > widest)
            widest = width;
    }

    bytes = (unsigned long)(widest + 8) * (unsigned long)(lineCount * 10 + 8);
    handle = mem_Alloc(bytes, 1, (char far *)0);
    if (handle == 0) {
        free(copy);
        return 0;
    }

    image = (unsigned char far *)mem_Lock(handle);
    if (image != 0) {
        image[0] = (unsigned char)widest;
        image[1] = (unsigned char)(widest >> 8);
        image[2] = (unsigned char)lineCount;
        image[3] = 0;
        font_MakeImage(copy, mode, (void far *)0);
        mem_Unlock(handle);
    }

    if (displayType == 2)
        ConvertMonoMaskToColor(handle);
    else if (displayType == 0x0a)
        ConvertMonoMaskToTandy(handle);

    free(copy);
    return handle;
}
