/*
 * Early PACK state words for editor and map setup.  Scycle's public interval
 * is one word; a separate recovered array view indexes backward from that
 * public anchor, so this definition owns only the named word itself.
 */
struct MapPoint {
    int x;
    int y;
};

int __based(__segname("PACK")) Scycle = 0;
int __based(__segname("PACK")) EditColumns = 0;
char far * __based(__segname("PACK")) MiscStrs = 0;
int __based(__segname("PACK")) LastQueenPlane = 0;
struct MapPoint __based(__segname("PACK")) EditDragPnt = {0, 0};
int __based(__segname("PACK")) SMode = 0;
int __based(__segname("PACK")) modeButtonState = 0;
int __based(__segname("PACK")) CurRestPlane = 0;
int __based(__segname("PACK")) StoreArray[5] = {0};
