/*
 * Render text into the shared image buffer.  The packed glyph map contains
 * the advance in its low byte and a source-row value in its high byte.
 */
struct OutBuffer {
    int imageOffset;
    int imageSegment;
    int height;
};

struct Font {
    int unused0[3];
    int cellWidth;
    int baselineAdjust;
    int unused1;
    int bitmapWidth;
    int height;
    unsigned char unused2[10];
    unsigned char far *bitmap;
    int far *glyphPosition;
    int far *glyphMap;
    int proportional;
    int fallbackGlyph;
};

extern int buffer_max_width;
extern int buffer_max_height;
extern struct OutBuffer far out_buffer;
extern int far source_bitmap_width;
extern int far dest_bitmap_width;
extern void far ClearBuffer(unsigned char far *buffer, unsigned int count);
extern void far DrawChar(unsigned char far *source, unsigned char far *destination,
    int left, int bottom, int top, int right);

void far * far font_MakeImage(char far *text, int imageOffset,
    struct Font far *font)
{
    int spacing;
    int width;
    int advance;
    int glyph;
    int right;
    int left;
    int top;
    int count;
    int index;
    int pos;

    ClearBuffer((unsigned char far *)out_buffer.imageOffset,
        buffer_max_width * buffer_max_height);
    source_bitmap_width = font->unused2[8] * 2;

    count = 0;
    if (font->proportional != 0) {
        spacing = 0;
        if (*text == 0)
            pos = imageOffset;
        else {
            advance = (unsigned char)font->glyphMap[font->fallbackGlyph];
            for (pos = 0; text[pos] != 0; ++pos) {
                glyph = font->glyphMap[(unsigned char)text[pos]];
                if (glyph != -1)
                    count += (unsigned char)glyph;
                else
                    count += advance;
                count += spacing;
            }
            pos = font->cellWidth;
        }
    }
    else {
        spacing = font->baselineAdjust < 0;
        count = font->cellWidth * strlen(text);
        pos = font->cellWidth;
    }

    dest_bitmap_width = (count + imageOffset + 7) >> 3;
    out_buffer.height = font->height;
    right = buffer_max_width * 8 - font->bitmapWidth;
    index = 0;

    if (*text == 0)
        pos = imageOffset;
    else {
        for (pos = imageOffset; right > pos; ) {
            glyph = font->glyphMap[(unsigned char)text[index]];
            if (glyph == -1)
                glyph = font->fallbackGlyph;
            top = (unsigned char)(font->glyphMap[glyph] >> 8);
            if (font->proportional != 0) {
                advance = (unsigned char)font->glyphMap[glyph];
                width = font->glyphPosition[glyph];
                left = -(width - font->glyphPosition[glyph + 1]);
                if (font->baselineAdjust < 0) {
                    spacing = 0;
                    ++advance;
                }
                else
                    spacing = top + font->baselineAdjust;
            }
            else {
                advance = font->cellWidth;
                width = 0;
                left = top;
            }
            DrawChar(font->bitmap + source_bitmap_width, (unsigned char far *)out_buffer.imageOffset,
                left, font->height - 1, width, pos + spacing);
            pos += advance;
            ++index;
            if (text[index] == 0)
                break;
        }
    }
    out_buffer.imageOffset = pos;
    --out_buffer.height;
    return (void far *)out_buffer.imageOffset;
}
