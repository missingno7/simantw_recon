struct Font {
    int header[13];
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
    int far *word;
    void far *stream;
    int i, tableCount, imageSize;

    font = (struct Font far *)mem_malloc(0x2a, "FontHeader");
    if (font == 0)
        return 0;

    stream = fopen(filename, "rb");
    if (stream == 0) {
        mem_free(font);
        return 0;
    }

    word = font->header;
    fread(word, 0x0d, 2, stream);
    for (i = 0; i < 13; ++i, ++word) {
        *word = (unsigned char)(*word >> 8) | ((unsigned int)(unsigned char)*word << 8);
    }

    if (font->header[7] > buffer_max_height) {
        mem_free(font);
        return 0;
    }

    tableCount = font->header[2] - font->header[1] + 3;
    imageSize = font->header[7] * font->header[12] * 2;
    font->image = (unsigned int far *)mem_malloc(imageSize, "FONTIMAGE");
    font->locTable = (unsigned int far *)mem_malloc(tableCount * 2,
                                                     "locTable");
    font->owTable = (unsigned int far *)mem_malloc(tableCount * 2,
                                                    "owTable");

    fread(font->image, imageSize, 1, stream);
    fread(font->locTable, 2, tableCount, stream);
    if (tableCount > 0) {
        word = (int far *)font->locTable;
        for (i = 0; i < tableCount; ++i, ++word) {
            *word = ((*word & 0xff) << 8) + ((unsigned int)*word >> 8);
        }
    }
    fread(font->owTable, 2, tableCount, stream);
    if (tableCount > 0) {
        word = (int far *)font->owTable;
        for (i = 0; i < tableCount; ++i, ++word) {
            *word = ((*word & 0xff) << 8) + ((unsigned int)*word >> 8);
        }
    }
    fclose(stream);

    font->noTypeFlag = (font->header[0] & 0x2000) == 0;
    font->charCount = font->header[2] - font->header[1] + 1;
    return font;
}
