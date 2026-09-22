extern int far EatCountB;
extern int near BpopT;
extern int near HealthB;
extern int far AlwaysHealthy;

void DecEatB(void)
{
    --EatCountB;
    if (EatCountB < 0) {
        EatCountB = BpopT >> 5;
        if (HealthB > 0 && !AlwaysHealthy)
            --HealthB;
    }
}
