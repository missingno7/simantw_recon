/* Eight- and nine-way direction step tables (x and y deltas) in the far simulation data segment. */
signed char __based(__segname("SIMANT_DATA_GROUP")) Dx8[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
signed char __based(__segname("SIMANT_DATA_GROUP")) Dy8[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
signed char __based(__segname("SIMANT_DATA_GROUP")) Dx9[10] = { 0, 0, 1, 1, 1, 0, -1, -1, -1, 0 };
signed char __based(__segname("SIMANT_DATA_GROUP")) Dy9[10] = { 0, -1, -1, 0, 1, 1, 1, 0, -1, 0 };
