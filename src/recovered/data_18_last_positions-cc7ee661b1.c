/*
 * The last exit, hole, egg and food-drop locations start as empty word pairs.
 * Queen-placement mode and the save-needed latch both start clear.
 */
int __based(__segname("SIMANT_DATA_GROUP")) LastNewExitB[2] = { 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) LastNewExitR[2] = { 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) LastNewHoleB[2] = { 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) LastNewHoleR[2] = { 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) LastBlackEgg[2] = { 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) LastRedEgg[2] = { 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) LastFoodDrop[2] = { 0, 0 };
int __based(__segname("SIMANT_DATA_GROUP")) LayDownQueenMode = 0;
int __based(__segname("SIMANT_DATA_GROUP")) gGameNeedsSaving = 0;
