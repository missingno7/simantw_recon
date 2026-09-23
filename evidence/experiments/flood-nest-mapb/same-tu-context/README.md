# FloodNestB adjacent member context

Compared the standalone candidate with the same candidate followed in one C7 source by the strictly admitted adjacent `_CompactListA`, `_CompactListB`, and `_CompactListR` sources. The selected `_FloodNestB` member stayed 60 bytes with 27/27 opcodes, seven register-only differences, and 1/1 `_MapB` fixup. The combined object gained the neighboring bodies and 49 total fixups; the selected member's codegen diagnostics were unchanged.

This rules out those tested following-member bodies as the cause of the register schedule. It does not prove the historical TU boundary or test predecessor bodies, since the immediately preceding `_FixExitMapB/R` members remain unresolved. The spec, sources, receipts, and compact comparison are preserved here.
