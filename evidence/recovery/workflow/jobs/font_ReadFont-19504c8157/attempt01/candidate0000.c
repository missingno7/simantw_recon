struct Font {
    unsigned int header[13];
    unsigned int far *image;
    unsigned int far *locTable;
    unsigned int far *owTable;
    int noTypeFlag;
    int charCount;
};

extern int near buffer_max_height;
extern void far *mem_malloc(unsigned int size, char far *tag);
extern void far mem_free(void far *ptr);
extern void far * far fopen(char far *filename, char far *mode);
extern unsigned int far fread(void far *buffer, unsigned int size,
                              unsigned int count, void far *stream);
extern int far fclose(void far *stream);

void far * far font_ReadFont(char far *filename)
{
    struct Font far *font;
    void far *stream;
    unsigned int far *word;
    unsigned int i;
    int tableCount;
    unsigned int height, rowWords;

    font = (struct Font far *)mem_malloc(0x2a, "FontHeader");
    if (font == 0)
        return 0;

    stream = fopen(filename, "rb");
    if (stream == 0) {
        mem_free(font);
        return 0;
    }

    fread(font, 0x0d, 2, stream);
    word = font->header;
    for (i = 13; i != 0; --i, ++word)
        *word = (unsigned int)((*word << 8) + (*word >> 8));

    if ((int)font->header[7] > buffer_max_height) {
        mem_free(font);
        return 0;
    }

    height = font->header[7];
    rowWords = font->header[12];
    font->image = (unsigned int far *)mem_malloc(height * rowWords * 2,
                                                 "FONTIMAGE");

    tableCount = (int)font->header[2] - (int)font->header[1] + 3;
    font->locTable = (unsigned int far *)mem_malloc(tableCount * 2,
                                                     "locTable");
    font->owTable = (unsigned int far *)mem_malloc(tableCount * 2,
                                                    "owTable");

    fread(font->image, 1, height * rowWords * 2, stream);
    fread(font->locTable, 2, tableCount, stream);
    for (i = (unsigned int)tableCount; i != 0; --i)
        font->locTable[i - 1] = (unsigned int)((font->locTable[i - 1] << 8) +
                                               (font->locTable[i - 1] >> 8));
    fread(font->owTable, 2, tableCount, stream);
    for (i = (unsigned int)tableCount; i != 0; --i)
        font->owTable[i - 1] = (unsigned int)((font->owTable[i - 1] << 8) +
                                              (font->owTable[i - 1] >> 8));
    fclose(stream);

    font->noTypeFlag = (font->header[0] & 0x2000) == 0;
    font->charCount = (int)font->header[2] - (int)font->header[1] + 1;
    return font;
}
