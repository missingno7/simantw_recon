# FloodNestB counter and address spellings

This isolated twelve-candidate C7 batch crossed four counter declaration forms (ordinary, row-only `register`, cell-only `register`, both `register`) with three equivalent byte-address forms (`MapB + row + cell`, reversed addition, and `&MapB[0][row + cell]`). All twelve candidates compiled to one OMF object (`770fe47da6cc...`), the same output as the earlier best class. The target comparison stayed 60 bytes, 27/27 opcodes, 1/1 `_MapB` fixup, and seven register-only byte differences.

This negative evidence is scoped to these local declaration and address spellings under baseline MSC7; it does not prove the register schedule is independent of all source lifetimes or translation-unit context. Full spec, generated sources, receipts, and compact comparisons are in this folder.
