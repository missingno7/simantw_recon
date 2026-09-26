/* The Microsoft C runtime caption pool: general run-time failure text,
 * floating-point diagnostics, and their preceding numeric message selectors.
 * Fixed character records retain the original packed offsets and embedded
 * NUL boundaries.
 */
struct RuntimeCaptionPool {
    char record00[80];
    char record01[80];
    char record02[80];
    char record03[80];
    char record04[80];
    char record05[80];
    char record06[80];
    char record07[80];
    char record08[80];
    char record09[80];
    char record10[80];
    char record11[8];
};
struct RuntimeCaptionPool __based(__segname("DGROUP")) _caption = {
        "C RUNTIME ERROR \000\000\000R6000\015\012- stack overflow\015\012\000\003\000R6003\015\012- integer divide by 0\015\012\000\011\000",
        "R6009\015\012- not enough space for environment\015\012\000\374\000\015\012\000\377\000run-time error \000\002\000R6002\015\012- fl",
        "oating-point support not loaded\015\012\000x\000DOMAIN error\015\012\000y\000SING error\015\012\000z\000TLOSS error\015",
        "\012\000e\000M6101: MATH\015\012- floating-point error: invalid\015\012\000f\000M6102: MATH\015\012- floating-poi",
        "nt error: denormal\015\012\000g\000M6103: MATH\015\012- floating-point error: divide by 0\015\012\000h\000M610",
        "4: MATH\015\012- floating-point error: overflow\015\012\000i\000M6105: MATH\015\012- floating-point erro",
        "r: underflow\015\012\000j\000M6106: MATH\015\012- floating-point error: inexact\015\012\000k\000M6107: MATH\015\012-",
        " floating-point error: unemulated\015\012\000l\000M6108: MATH\015\012- floating-point error: squar",
        "e root\015\012\000m\000M6109: MATH\015\012- floating-point error: integer overflow\015\012\000n\000M6110: MATH",
        "\015\012- floating-point error: stack overflow\015\012\000o\000M6111: MATH\015\012- floating-point error",
        ": stack underflow\015\012\000p\000M6100: MATH\015\012- floating-point error: explicitly generated\015",
        "\012\000\377\377\377\000\000\000"
};
