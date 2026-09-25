/* Window-edit dimensions, edit-message counters, flags, and the far buffer pointer. */
int near tileWidth = 16;
int near tileHeight[5] = { 16, 0, 0, 0, 0 };
int near editMessage[2] = {0};
long near editMessageRemoveTime = {0};
int near editForce = 1;
int near editBuf = {0};
char far * near theEditBufPtr = {0};
