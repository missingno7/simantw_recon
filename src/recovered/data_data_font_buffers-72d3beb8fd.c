/* Font image limits and resource names: the width and height words are 80
 * and 16; the height contribution continues with the font file signatures
 * consumed by the font reader. source_bitmap_width is the zeroed drawing
 * scratch used by DrawChar.
 */
int __based(__segname("DGROUP")) buffer_max_width = 80;
struct FontHeightAndResourceNames {
    int height;
    char names[40];
    char trailingNames[6];
};
struct FontHeightAndResourceNames __based(__segname("DGROUP")) buffer_max_height = {
    16,
    "FontHeader\000rb\000FONTIMAGE\000locTable\000owTable",
    "\000\000\000\000\000\000"
};
int __based(__segname("DGROUP")) source_bitmap_width = 0;
