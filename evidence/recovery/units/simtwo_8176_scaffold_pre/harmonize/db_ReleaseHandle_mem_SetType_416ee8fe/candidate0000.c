/* Candidate reconstruction of the database release wrapper. */
extern void far mem_SetType(int handle, int type);

void db_ReleaseHandle(unsigned int handle)
{
    mem_SetType(handle, 3);
}
