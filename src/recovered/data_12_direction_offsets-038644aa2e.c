/*
 * Four-direction movement and seating offsets stay paired with the small
 * animation-index lookup used by the ant placement code.
 */
int __based(__segname("SIMANT_DATA_GROUP")) SpX[4] = {
    0x0300, 0x0304, 0xfd00, 0xfdfc
};
int __based(__segname("SIMANT_DATA_GROUP")) SpY[4] = {
    0xfdfc, 0x0300, 0x0304, 0xfd00
};
int __based(__segname("SIMANT_DATA_GROUP")) SeatX[4] = {
    0x0100, 0x0101, 0xff00, 0xffff
};
int __based(__segname("SIMANT_DATA_GROUP")) SeatY[4] = {
    0xffff, 0x0100, 0x0101, 0xff00
};
int __based(__segname("SIMANT_DATA_GROUP")) AnTab[4] = {
    0, 1, 2, 1
};
