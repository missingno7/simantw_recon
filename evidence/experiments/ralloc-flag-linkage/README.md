# Warning flag linkage control

The best preserved `_RallocFindMem` body is ordinary attempt 5: 330 candidate
bytes against 329 target bytes, with byte-identical 118-byte private DATA.
The first code difference at +C4 is target `MOV DX,[0880]; OR DX,DX` versus
candidate `CMP word ptr [0880],0`. Attempt 3 already showed that copying the
flag into a `register int` local does not change C7's instruction choice.

This isolated probe changes only `lowMemoryReported` from a `static` to a
public near definition. It tests whether C7's linkage/alias assumptions
explain the load. Authentic baseline compilation still emits the memory
compare at +C4 and a 330-byte body. The object hash differs because the
public symbol/private-data representation changes, but that is no codegen
solution and does not establish public historical linkage. The source,
receipt, and complete comparison are in `public-flag-trial/`. Do not promote
this spelling or spend another production attempt on linkage alone.
