/* The near DGROUP handle stores the start of the packed-data region in PACK. */
extern char __based(__segname("PACK")) match_position[];
void far * __based(__segname("DGROUP")) unpackHandle = (void far *)match_position;
