# Popup menu loop and far result pointer

The target `_ms_PopUpMenuResource` is 320 bytes at GR_MODULE:514C. Its
`AppendMenu` paths each compute `(index + 1) | 0xF900` immediately before
the call. The prior six-attempt candidate precomputed that value outside the
branch and was 330 bytes. Ordinary attempt 7 split `itemText = *cursor + 1`
into an assignment and increment; MSC 7.00 emitted the same object as
attempt 6, so that source spelling is a negative control. Ordinary attempt 8
moved the item-number expression into each call. It reproduced the target's
two `LEA AX,[SI+1]; OR AH,F9; PUSH AX` sequences and reduced the candidate
to 324 bytes. Its complete-member comparison still rejected the code and
fixups. Sources, receipts, and full reports are in the job's attempt07/08
directories; the two controlled source drafts are here.

The target at +D5 loads `popUpMenuId`'s 80EE offset and C6C2 selector into
ES:BX, stores both words at BP-1A/-18, clears ES:[BX], and reads through
that saved far pointer at +116..+12B. Attempt 8 instead accessed the far
global directly and had a 22-byte frame against the target's 26 bytes.
Expert attempt 9 tested `int far *chosen = &popUpMenuId` and reads through
`chosen`, using one DATA_IDENTITY hypothesis extension that preserved all
eight earlier attempts. C7 emitted the indirect clear, but kept the offset
in DI and only stored the segment, leaving the frame 22 bytes and growing
the body to 334 bytes. This rules out that simple pointer spelling as a
complete explanation; it does not disprove the target's observed pointer
local. Attempt 8 remains the best source hypothesis. The unresolved cause
is the earlier items/cursor and result-pointer lifetimes that determine
stack placement and register retention, followed by complete unit bindings.
