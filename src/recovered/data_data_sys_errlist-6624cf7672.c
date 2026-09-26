/* The 38 far entries point into the measured DGROUP error-text block. */
struct CrtErrorText {
    char part00[80];
    char part01[80];
    char part02[80];
    char part03[68];
};
struct CrtCtypeData {
    unsigned char classification[257];
    unsigned char runtimePrefix[5];
    struct CrtErrorText errors;
};
extern struct CrtCtypeData __based(__segname("DGROUP")) _ctype_;
char far * __based(__segname("DGROUP")) sys_errlist[38] = {
    (char far *)&_ctype_.errors.part00[0],
    (char far *)&_ctype_.errors.part00[8],
    (char far *)&_ctype_.errors.part00[9],
    (char far *)&_ctype_.errors.part00[35],
    (char far *)&_ctype_.errors.part00[36],
    (char far *)&_ctype_.errors.part00[37],
    (char far *)&_ctype_.errors.part00[38],
    (char far *)&_ctype_.errors.part00[39],
    (char far *)&_ctype_.errors.part00[57],
    (char far *)&_ctype_.errors.part00[75],
    (char far *)&_ctype_.errors.part01[11],
    (char far *)&_ctype_.errors.part01[12],
    (char far *)&_ctype_.errors.part01[13],
    (char far *)&_ctype_.errors.part01[29],
    (char far *)&_ctype_.errors.part01[47],
    (char far *)&_ctype_.errors.part01[48],
    (char far *)&_ctype_.errors.part01[49],
    (char far *)&_ctype_.errors.part01[50],
    (char far *)&_ctype_.errors.part01[62],
    (char far *)&_ctype_.errors.part02[0],
    (char far *)&_ctype_.errors.part02[1],
    (char far *)&_ctype_.errors.part02[2],
    (char far *)&_ctype_.errors.part02[3],
    (char far *)&_ctype_.errors.part02[20],
    (char far *)&_ctype_.errors.part02[21],
    (char far *)&_ctype_.errors.part02[41],
    (char far *)&_ctype_.errors.part02[42],
    (char far *)&_ctype_.errors.part02[43],
    (char far *)&_ctype_.errors.part02[44],
    (char far *)&_ctype_.errors.part02[68],
    (char far *)&_ctype_.errors.part02[69],
    (char far *)&_ctype_.errors.part02[70],
    (char far *)&_ctype_.errors.part02[71],
    (char far *)&_ctype_.errors.part02[72],
    (char far *)&_ctype_.errors.part03[6],
    (char far *)&_ctype_.errors.part03[23],
    (char far *)&_ctype_.errors.part03[24],
    (char far *)&_ctype_.errors.part03[54]
};
