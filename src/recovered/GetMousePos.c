/* Byte-matched reconstruction of the USER GetCursorPos wrapper. */
extern int far pascal GetCursorPos(void far *point);

int GetMousePos(void far *point)
{
    return GetCursorPos(point);
}
