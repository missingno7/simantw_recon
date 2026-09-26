/* The public begins with nineteen DGROUP far pointers. Their text targets
 * remain at their measured relative offsets beyond this pointer table. */
union CommandStringTable {
    char far *entries[19];
    char bytes[76];
};

union CommandStringTable __based(__segname("DGROUP")) commandStr = {
    {
        (char far *)&commandStr.bytes[82],
        (char far *)&commandStr.bytes[89],
        (char far *)&commandStr.bytes[98],
        (char far *)&commandStr.bytes[105],
        (char far *)&commandStr.bytes[113],
        (char far *)&commandStr.bytes[119],
        (char far *)&commandStr.bytes[129],
        (char far *)&commandStr.bytes[139],
        (char far *)&commandStr.bytes[155],
        (char far *)&commandStr.bytes[165],
        (char far *)&commandStr.bytes[185],
        (char far *)&commandStr.bytes[192],
        (char far *)&commandStr.bytes[199],
        (char far *)&commandStr.bytes[211],
        (char far *)&commandStr.bytes[226],
        (char far *)&commandStr.bytes[244],
        (char far *)&commandStr.bytes[261],
        (char far *)&commandStr.bytes[278],
        (char far *)&commandStr.bytes[295]
    }
};
