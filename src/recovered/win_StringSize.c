/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern int far font_StringWidth(int first, int second);
extern int far font_FontHeight(void);

long win_StringSize(int first, int second)
{
    union {
        long value;
        struct {
            int width;
            int height;
        } parts;
    } result;
    result.parts.width = font_StringWidth(first, second);
    result.parts.height = font_FontHeight();
    return result.value;
}
