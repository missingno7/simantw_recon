# HistUpdate local declaration order probe

This isolated follow-up starts from `evidence/experiments/histupdate-named-buffers-20260924/candidate.c`, the best saved named-H-buffer draft. The historical instruction on local order was reviewed in `docs/grinder-lessons.md` around line 221. The earlier ColonySmellBN pointer-lifetime experiment concerns a different function and provides no HistUpdate-specific local-allocation evidence; here the direct target-vs-candidate loop register schedule is the bounded hypothesis.

Three semantics-equivalent permutations changed only the order of declarations `hs`, `p`, `i`, and `v`. The fixed body leaves every local assigned before use. Setup/source hashes and variant order are in `setup.json`; the exact compiler batch and all strict comparisons are in `run/results.json`.

## Result

All 3 candidates compiled under the current baseline MSC7 profile. All produced the same effective OMF: 1239 bytes, SHA-256 `7e0374c8671c18ab13ffedcc9205526dd3c53b0ee01abd0a4d6836b8a9cd47d1`. This is the same OMF as the prior named-buffer experiment; declaration ordering added no new output class.

Every candidate remains `NO_COMPLETE_MATCH`: 322 bytes versus target 317, 84/93 opcodes, CFG match true, instruction layout false, 9/322 literal bytes, and 0/74 fixups. The candidate keeps the same register set and the redraw loop retains the same mismatch: target DI index + SI pointer versus candidate SI index + stack-spilled pointer `[bp-2]`. Native `tu_assembly.body_exact` therefore remains false. No output improved the body gate or residue.

Conclusion: these three declaration orders collapse to one compiler output. Stop this axis; no further permutation, production reissue, or promotion is justified by this result.
