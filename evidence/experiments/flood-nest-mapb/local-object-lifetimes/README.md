# FloodNestB pointer and value lifetimes

A four-candidate C7 batch compared the best corrected `MapB` source with: (1) the baseline pointer plus `int value`; (2) pointer access without a saved value; (3) direct flat-array indexing without a pointer temporary; and (4) the pointer plus `unsigned char value`. Each produced a distinct OMF output. The baseline remained best at 60 bytes, 27/27 aligned opcodes, 1/1 exact `_MapB` fixup, and seven register-only mismatches (target DI/BX; candidate CX/DI). Removing the value/pointer caused broad code and fixup regressions; changing `value` to `unsigned char` emitted 56 bytes with 22/27 opcodes and eight register differences.

This shows the tested pointer/value lifetimes control codegen, but these alternatives do not reproduce the target schedule. Full sources, receipts, and compact outcomes are in this folder.
