# HistUpdate named H-buffer identity experiment

Scope: isolated experiment only. One source change set replaces the nine fabricated `histBuf*` identities in the preserved attempt02 draft with target-proven `_H_*` MAPSYM identities. The source SHA used by the compiler was `9961e02c834bf2844fe19b9cf9bf7ca53b54a84b299f99716f0c1b6ffe553bf5`.

## Evidence and mapping

The names come from `src/recovered/wf_ClearHistory-2a7aae3cf9.c` and its native promotion proof. Its OMF fixups and `evidence/symbols/symbol-address-map.json` map H arrays to SEG9 offsets. The HistUpdate factory packet independently labels the direct segment-9 operands. Nine draft identities were changed; `match_position[hs]` was deliberately left as-is because the instruction constrained the edit to fabricated `histBuf*` identities. The exact source/base hashes and per-name mapping are in `mapping.json`.

## Strict result

One baseline MSC 7.00 compile was run with `/AL /G2 /Gs /Oelw /NTSIMANT_MODULE` using `spec.json` and `run01/results.json`.

- Strict result: `NO_COMPLETE_MATCH`; native `tu_assembly.body_exact` is false.
- Extent: candidate 322 bytes, target 317 bytes.
- Opcode alignment: 84/93; CFG shape matches; layout does not.
- Literal bytes: 9/322 equal.
- Fixups: 0/74 equal. Private CONST placement conflicts and unresolved/mismatched SIMANT_MODULE fixups remain.
- Candidate OMF SHA-256: `7e0374c8671c18ab13ffedcc9205526dd3c53b0ee01abd0a4d6836b8a9cd47d1` (1239 bytes), distinct from both preserved job OMFs. This is one unique new effective OMF.

## Residual body evidence

The first structural difference is target `push di` at offset 4, absent in the candidate. The main remaining code-shape cluster is the redraw loop: target uses DI as the index and SI as the pointer (`xor di,di; mov si,0x8e54; ... inc di; add si,2; cmp si,0x8e5c`); this candidate uses SI as index, spills the pointer to `[bp-2]`, and loads values through CX/BX. The draft source has `p`, `i`, and `v` locals, but no admitted neighboring source evidence ties a specific source rewrite to the target register allocation. The evidence supports identifying this as the largest concrete shape residue, but not choosing a safe next source form. No second compile is justified from the current evidence.

No production job, proof, manifest, ledger, or tool was edited; no candidate was promoted.
