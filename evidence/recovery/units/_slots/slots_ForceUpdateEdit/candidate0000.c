/* Candidate reconstruction of the edit-update thunk. */
extern void far UpdateEdit(void);

void ForceUpdateEdit(void)
{
    UpdateEdit();
}
