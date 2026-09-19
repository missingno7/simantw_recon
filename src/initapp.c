/* Six-byte Win16 application initialization wrapper; original names from SYM.
 * Void prototypes are semantic candidates, not recovered debug type records.
 */
extern void far initStuff(void);

void far InitApplicationStuff(void)
{
    initStuff();
}
