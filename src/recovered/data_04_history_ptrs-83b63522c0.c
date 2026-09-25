/*
 * The two history graph tables select the population and condition arrays
 * held in PACK.  Each table retains its original black/red series order.
 */

extern int __based(__segname("PACK")) H_BPop[64];
extern int __based(__segname("PACK")) H_BFood[64];
extern int __based(__segname("PACK")) H_BHeal[64];
extern int __based(__segname("PACK")) H_FoodA[64];
extern int __based(__segname("PACK")) H_ADead[64];
extern int __based(__segname("PACK")) H_RPop[64];
extern int __based(__segname("PACK")) H_RFood[64];
extern int __based(__segname("PACK")) H_RHeal[64];
extern int __based(__segname("PACK")) H_PDead[64];
extern int __based(__segname("PACK")) H_FDead[64];

int far * __based(__segname("SIMANT_DATA_GROUP")) HistGraphs[10] = { H_BPop, H_BFood, H_BHeal, H_FoodA, H_ADead, H_RPop, H_RFood, H_RHeal, H_PDead, H_FDead };
int far * __based(__segname("SIMANT_DATA_GROUP")) AltHistGraphs[10] = { H_RPop, H_RFood, H_RHeal, H_FoodA, H_FDead, H_BPop, H_BFood, H_BHeal, H_FDead, H_PDead };
