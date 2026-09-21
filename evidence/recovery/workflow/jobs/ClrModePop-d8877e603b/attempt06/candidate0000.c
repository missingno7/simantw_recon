/* Exact PACK names and bounded 20-word loops; named-segment based objects
 * test the original immediate-selector and temporary-DS access pattern.
 */
extern unsigned int __based(__segname("PACK")) TemRModePop[];
extern unsigned int __based(__segname("PACK")) TemBModePop[];
extern unsigned int __based(__segname("PACK")) FlyAwayB;
extern unsigned int __based(__segname("PACK")) FlyAwayR;
void near ClrModePop(void)
{
    int i;
    for (i=0;i<20;++i) TemRModePop[i]=0;
    for (i=0;i<20;++i) TemBModePop[i]=0;
    if (FlyAwayB != 0) --FlyAwayB;
    if (FlyAwayR != 0) --FlyAwayR;
}
