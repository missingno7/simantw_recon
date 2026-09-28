/* Meta probe: aggregate far-pointer slots and coordinate local ordering. */
struct Slots { int far *handle; int far *balloon; };
extern int far yardBalloonHandle;
extern int far yardBalloon;
extern void far Touch(void);
void far DrawSimKid(void)
{
    int y;
    struct Slots slots;
    int x;
    y = 2;
    x = 1;
    slots.handle = &yardBalloonHandle;
    slots.balloon = &yardBalloon;
    Touch();
    *slots.handle = x;
    Touch();
    *slots.balloon = y;
}
