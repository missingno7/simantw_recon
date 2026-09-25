/*
 * IBM startup tests this two-byte debug switch. The DGROUP public is zero
 * initialized in the original initialized-data contribution.
 */
int near debugOn = 0;
