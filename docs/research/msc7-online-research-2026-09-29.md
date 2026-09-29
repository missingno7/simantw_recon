# Online research: MSC 7.00 and SimAnt for Windows (2026-09-29)

Summary of an external web-research report commissioned by the project owner. The claims are the researcher's, with their sources; none is verified against our toolchain unless stated.

## Allocator (/Oe)
- The C6 *Advanced Programming Techniques* manual (§1.5.8) says /Oe ignores `register` declarations and allocates registers to "variables or subexpressions according to frequency of use". Candidates include SUBEXPRESSIONS, not only named variables, and values can be spilled.
- No public documentation of weights, loop weighting, tie-breaks, live ranges, SI/DI/BX/CX selection or stack-home order was found.
- The manual's "Register Candidates" table concerns `_fastcall` argument passing, not local allocation.
- KB Q61055: a C6 `/Ole` failure names the internal source file `regMD.c:1.100`. The article has a small reproducer (an unsigned parameter plus a loop), usable as a fingerprint probe.

## Pragmas
- C6 documents `#pragma optimize("aceglwnptz", on|off)`. Letters: a (no aliasing), c (local CSE), e (global register allocation), g (global CSE), l (loops), w (no aliasing except across calls), n (disable unsafe loop optimisations), p (float consistency), t (speed), z (accepted; more aggressive).
- The KB shows function-level wrapping (`optimize("e", off)` ... `optimize("e", on)`).
- `optimize("", off)` disables all optimisation; `("", on)` restores the command-line state.
- `loop_opt(on|off|)` governs FOLLOWING functions.
- Our own trial is fact MSC7-P1.

## Compiler passes and patches
- /B1 /B2 /B3 select passes. /Fa and /Fc give listings. No documented allocator or IL dump.
- **C7PATCH.ZIP**: LINK 5.31.009, LIB 3.20.010, IMPLIB 1.40.005, CodeView. No replacement C23216 is listed. Our LINK is locked at 5.30.
- **C7PATB.ZIP** patches CL.EXE and MS32KRNL.DLL. Its README says "compiling the same source file twice may produce different size .OBJ files when compiling under Windows". A Windows-hosted memory problem.
  - Hypothesis to test: the original build may have been affected by memory-dependent compiler behaviour, e.g. optimisation reduced for lack of heap. Our captured pass-2 flags include `-Bm 2048`.
- ENTER/LEAVE: C6 `/G2` can emit ENTER/LEAVE but `/Gw` overrides it. C7 supports Windows ENTER/LEAVE prologues with `/GA` or `/GD` plus `/G2`.

## C23216.EXE format (early non-COFF PE; KB Q123667: DOSX32 via MS32KRNL.DLL)
Fields, relative to the "PE\0\0" header:

| Offset | Field |
|---|---|
| 0x24 | EntryPointRVA |
| 0x28 | ImageBase |
| 0x50 | NumberOfObjects |
| 0x54 | ObjectTableRVA |
| 0x6C | NumberOfSpecialRVAs |

- Each object entry is six dwords: RVA, VirtualSize, SeekOffset, OnDiskSize, ObjectFlags, Reserved.
- Mapping: `VA = ImageBase + RVA + (file_offset - SeekOffset)`, within OnDiskSize only.
- ObjectTableRVA is an RVA.
- Sources: Hermès Bélusca-Maïto's NTPEConv (doc_format.md, nt196pe.h). `NTPECONV -v -t C23216.EXE` is untested against C7.

## Provenance
- Windows programming credits: Daniel Goldman and Rodney Lai. Goldman also did the DOS version. Design: Will Wright and Justin McCormick.
- No public SimAnt source was found.
- The Strong: Will Wright collection 2013.wright.will (design notebooks) and the Kevin O'Hare collection; no catalogued SimAnt source.
- Sister Win16 NE builds: WGAIA.EXE (SimEarth), SIMLIFEW.EXE, WSIMFARM.EXE, SIMTOWER.EXE, SimCity Classic, RoboSport, SimCity 2000 Win16. Compiler and symbols are unknown.
- Re-releases: SimClassics 3-in-1 (1996; "SimAnt and SimFarm are newly ported to Windows for this compilation") and My 3 Sims (1997).

## Build practice
- /PACKCODE and /PACKDATA coalesce neighbouring segments. Far communal variables go to private paragraph-aligned FAR_BSS segments (compare our LINK-D1).
- A 1992 Microsoft sample (Zusammen/Picker, Dale Rogerson) documents per-module flags, /GA and /GD, and _loadds.
