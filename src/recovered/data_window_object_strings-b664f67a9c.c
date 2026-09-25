/*
 * winObjStr is the window library's 23-entry far-pointer table followed by
 * its packed object-kind/format strings. Each pointer names its string within
 * this public object. The final NUL is the following byte in the same DGROUP
 * contribution; later diagnostic literals belong to code members.
 */
struct WindowObjectStringTable {
    char far *entry[23];
    char text[178];
};

struct WindowObjectStringTable __based(__segname("DGROUP")) winObjStr = {
    {
        (char far *)&winObjStr.text[0],
        (char far *)&winObjStr.text[9],
        (char far *)&winObjStr.text[14],
        (char far *)&winObjStr.text[24],
        (char far *)&winObjStr.text[29],
        (char far *)&winObjStr.text[34],
        (char far *)&winObjStr.text[41],
        (char far *)&winObjStr.text[48],
        (char far *)&winObjStr.text[56],
        (char far *)&winObjStr.text[64],
        (char far *)&winObjStr.text[71],
        (char far *)&winObjStr.text[76],
        (char far *)&winObjStr.text[81],
        (char far *)&winObjStr.text[87],
        (char far *)&winObjStr.text[96],
        (char far *)&winObjStr.text[101],
        (char far *)&winObjStr.text[109],
        (char far *)&winObjStr.text[119],
        (char far *)&winObjStr.text[129],
        (char far *)&winObjStr.text[141],
        (char far *)&winObjStr.text[150],
        (char far *)&winObjStr.text[159],
        (char far *)&winObjStr.text[169]
    },
    "Backdrop\0Area\0Rectangle\0Menu\0List\0Button\0Bitmap\0"
    "HSlider\0VSlider\0String\0Text\0Line\0Title\0BmButton\0"
    "Poly\0Outline\0FormatStr\0FormatBut\0FormatTitle\0"
    "HOutline\0VOutline\0HBackdrop\0VBackdrop"
};

static char __based(__segname("DGROUP")) WinObjStringEnd = 0;
