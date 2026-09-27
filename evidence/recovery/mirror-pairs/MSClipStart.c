/* Derived mechanically from the mirrored colony function _MSClipEnd (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped MSClipEnd->MSClipStart; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/* Supervisor hypothesis: Two adjacent private zero-initialized saved GDI selection handles; complete four-byte BSS contribution and all bindings must match. */
/*
 * MSClipEnd restores the two optional GDI selections made by MSClipStart.
 * The palette selection is released with USER's SelectPalette; a saved GDI
 * object is restored with GDI's SelectObject and then cleared.  Finally the
 * window/DC pair is released and both clip handles are reset to zero.
 */
static int near clipPalette;
static int near clipObject;
extern int near clipWind;
extern int near clipDC;
extern int far pascal SelectPalette(int dc, int palette, int forceBackground);
extern int far pascal SelectObject(int dc, int object);
extern int far pascal ReleaseDC(int window, int dc);

void MSClipStart(void)
{
    if (clipPalette != 0)
        SelectPalette(clipDC, clipPalette, 0);

    if (clipObject != 0) {
        SelectObject(clipDC, clipObject);
        clipObject = 0;
    }

    ReleaseDC(clipWind, clipDC);
    clipWind = 0;
    clipDC = 0;
}
