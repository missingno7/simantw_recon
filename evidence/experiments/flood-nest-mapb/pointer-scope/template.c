/*
 * FloodNestB updates the B-side nest cells in the shared map.  Each row
 * starts at offset three and spans the remaining 0x3d cells.  Values in the
 * flooding band 0x20..0x2d receive the flood increment; low values at or
 * below 0x13 become the full-water marker 0x50.
 */
extern unsigned char near MapB[];

@FUNCTION@
