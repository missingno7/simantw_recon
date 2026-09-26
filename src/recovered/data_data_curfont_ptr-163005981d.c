/* Font entry points consume this four-byte offset:selector pair. */
struct FarAddress {
    unsigned int lo;
    unsigned int hi;
};
struct FarAddress __based(__segname("DGROUP")) curFontPtr = { 0, 0 };
