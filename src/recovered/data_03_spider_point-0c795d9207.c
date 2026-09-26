/*
 * PreDrawSpider writes only the x and y words at PACK:8124h and PACK:8126h.
 * Those are the two fields of the MapPoint declaration used by admitted
 * code.  No indexed access in the inspected code reaches the rest of the
 * 6316-byte public span, so this claims the four-byte point alone.
 */
struct MapPoint { int x; int y; };
struct MapPoint __based(__segname("PACK")) spiderBuf = {0};
