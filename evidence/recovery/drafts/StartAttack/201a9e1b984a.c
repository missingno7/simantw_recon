/*
 * Begin the attack phase: choose a random delay in the historical range
 * 30..129, publish it in the simulation state, start the attack song, and
 * open the edit message using the current message object's two stored words.
 * The large padding fields document the private far-state offsets seen in
 * the original SIMTWO module; they are not guessed loader addresses.
 */
struct AttackState {
    unsigned char pad[0x78dc];
    unsigned int attackDelay;
};

struct EditMessageObject {
    unsigned char pad[0x14];
    unsigned int first;
    unsigned int second;
};

struct AttackWindows {
    unsigned char pad[0x7c94];
    struct EditMessageObject far *message;
};

extern struct AttackState far attackState;
extern struct AttackWindows far attackWindows;
extern int far SRand1(unsigned int range);
extern void far myBeginSong(unsigned int song, unsigned int mode);
extern void far EditMessage(int first, int second, int width,
                            int fourth, int fifth);

void StartAttack(void)
{
    attackState.attackDelay = SRand1(100) + 30;
    myBeginSong(0x2b0a, 0x3f);
    EditMessage(attackWindows.message->first,
                attackWindows.message->second, 0x78, 0, 0);
}
