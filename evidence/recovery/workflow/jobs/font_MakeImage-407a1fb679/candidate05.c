/*
 * Hypothesis: the target keeps the glyph-position expressions live through
 * the draw call instead of assigning separate width/left/top locals. This
 * should let C7 reuse the target's smaller frame while preserving direct
 * far-pointer arguments.
 */
struct OutBuffer { int width; int height; void far *image; };
struct Font {
    int unused0[3];
    int cellWidth;
    int baselineAdjust;
    int unused1;
    int bitmapWidth;
    int height;
    unsigned char unused2[8];
    int sourceWidth;
    unsigned char far *bitmap;
    int far *glyphPosition;
    int far *glyphMap;
    int proportional;
    int fallbackGlyph;
};
extern int buffer_max_width, buffer_max_height;
extern struct OutBuffer far out_buffer;
extern int far source_bitmap_width, dest_bitmap_width;
extern void far ClearBuffer(unsigned char far *, unsigned int);
extern void far DrawChar(unsigned char far *, unsigned char far *, int, int, int, int);
void far * far font_MakeImage(char far *text, int imageOffset, struct Font far *font)
{
    int spacing, width, advance, glyph, right, left, count, index, pos;
    int savedOffset, savedCellWidth;
    savedOffset = imageOffset;
    savedCellWidth = font->cellWidth;
    ClearBuffer((unsigned char far *)out_buffer.image,
        buffer_max_width * buffer_max_height);
    source_bitmap_width = font->sourceWidth * 2;
    count = 0;
    if (font->proportional != 0) {
        spacing = 0;
        if (*text == 0)
            pos = savedOffset;
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
            pos = savedCellWidth;
        }
    } else {
        spacing = font->baselineAdjust < 0;
        count = savedCellWidth * strlen(text);
        pos = savedCellWidth;
    }
    dest_bitmap_width = (count + savedOffset + 7) >> 3;
    out_buffer.height = font->height;
    right = buffer_max_width * 8 - font->bitmapWidth;
    index = 0;
    if (*text == 0)
        pos = savedOffset;
    else {
        for (pos = savedOffset; right > pos; ) {
            glyph = font->glyphMap[(unsigned char)text[index]];
            if (glyph == -1)
                glyph = font->fallbackGlyph;
            if (font->proportional != 0) {
                advance = (unsigned char)font->glyphMap[glyph];
                width = font->glyphPosition[glyph];
                left = -(width - font->glyphPosition[glyph + 1]);
                if (font->baselineAdjust < 0) {
                    spacing = 0;
                    ++advance;
                } else
                    spacing = (unsigned char)(font->glyphMap[glyph] >> 8)
                        + font->baselineAdjust;
            } else {
                advance = savedCellWidth;
                width = 0;
                left = (unsigned char)(font->glyphMap[glyph] >> 8);
                spacing = 0;
            }
            DrawChar(font->bitmap + source_bitmap_width,
                (unsigned char far *)out_buffer.image, left,
                font->height - 1, width, pos + spacing);
            pos += advance;
            ++index;
            if (text[index] == 0)
                break;
        }
    }
    out_buffer.width = pos;
    --out_buffer.height;
    return &out_buffer;
}


