# `_ClearHistory` volatile based-array negative

## Hypothesis

`volatile` on each otherwise distinct `static __based(__segname("PACK"))` array might stop MSC 7 from reusing the PACK selector across adjacent clears, while keeping each based object's offset as an ordinary immediate. This was a new qualifier probe; it does not repeat the five static/extern, based/far declaration forms already documented in `evidence/experiments/clear-history-based/README.md` and the blocked job reason.

## Result

One controlled candidate compiled under the assigned baseline profile. Strict comparison remained `NO_COMPLETE_MATCH`: 267 candidate code bytes, 82/90 opcodes, and 1/68 fixups. The target body is 299 bytes with 90/90 aligned opcodes in the preserved attempt03. The candidate still has unresolved PACK/CONST placement and fixups, and its selector reloads do not match the target's nine distinct ES reloads.

Most decisively, the candidate's effective OMF is byte-identical to the existing `trial` candidate 0 (tentative uninitialized based statics): 1,082 bytes, SHA-256 `0c0f329c678c35d8bd0e63bc3beada5405fb3cc1efe3f6336b386afb14e3405f`. The volatile qualifier collapses into an existing failed output class and adds no selector-reload behavior.

## Preserved evidence and remaining question

- `spec.json`: one-value bounded hypothesis and the exact template/declarations.
- `run/candidate0000.c`, `run/results.json`, and `run/candidate0000.diff.txt`: compiled source, receipt/OMF identity, full strict comparison, and compact difference.
- `evidence.json`: full codegen batch evidence.

No production job, source, manifest, or proof tool was changed. The remaining question is what real `simant:8A76` unit declaration and placement evidence gives each of the nine unnamed PACK ranges its own selector slot and plain literal offset, despite all nine ranges sharing the PACK segment. Existing isolated forms either CSE the selector or leave the offsets unresolved; another based/far spelling probe is not supported by this result.
