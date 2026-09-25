/*
 * TurnTab stores the eight-way turn-distance matrix used by ant movement.
 * The rows and columns are the eight direction indices.
 */
signed char __based(__segname("SIMANT_DATA_GROUP")) TurnTab[8][8] = {
    { 0, 1, 1, 1, 7, 7, 7, 7 }, 
    { 0, 1, 2, 2, 2, 2, 0, 0 }, 
    { 1, 1, 2, 3, 3, 3, 3, 1 }, 
    { 2, 2, 2, 3, 4, 4, 4, 4 }, 
    { 3, 3, 3, 3, 4, 5, 5, 5 }, 
    { 6, 6, 4, 4, 4, 5, 6, 6 }, 
    { 7, 7, 7, 5, 5, 5, 6, 7 }, 
    { 0, 0, 0, 0, 6, 6, 6, 7 }
};
