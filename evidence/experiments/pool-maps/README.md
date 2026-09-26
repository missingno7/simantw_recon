# Selector pool maps

These maps attribute private MSC 7.00 selector words in topology components that still contain at least one unadmitted function. They are source identity evidence, not recovery credit.

## Method

The generator reads `evidence/topology/build-topology.json`, disassembly cards, the fixture NE relocation chains, and MAPSYM publics. For each pool word it records the chain relocation and target segment, then finds every instruction in component members that loads that word. It records explicit `ES:` accesses linearly until the next ES write or `LES`, retaining function and code addresses plus instruction bytes.

Each numeric `ES:` displacement is checked against MAPSYM public extents. Candidate spans are loaded from `python tools/context.py --list --data`; every final resolved public is also queried with `python tools/context.py --data PUBLIC --brief` and that packet extent is recorded in the map. An exact public start is HIGH confidence; a single containing public extent is MEDIUM; conflicting, missing, or non-unique evidence is UNRESOLVED. MAPSYM span-to-next-public remains an extent bound, not a claim about C type or private-object ownership.

Generate the maps and this index with `python build/workers/pool-maps/pool_maps.py`. The optional `--notes` mode audits best drafts using `python tools/context.py SYMBOL --history` and records only aligned, confirmed selector binding differences through `python tools/search.py SYMBOL --note ...`.

## Index

| Component | Pool words | Resolved | Unresolved | Unadmitted members | Evidence |
|---|---:|---:|---:|---:|---|
| `simant:01B6` | 44 | 39 | 5 | 14 | [simant_01B6.json](simant_01B6.json) |
| `simant:469E` | 2 | 2 | 0 | 1 | [simant_469E.json](simant_469E.json) |
| `simant:4C24` | 8 | 6 | 2 | 3 | [simant_4C24.json](simant_4C24.json) |
| `simant:5530` | 20 | 16 | 4 | 6 | [simant_5530.json](simant_5530.json) |
| `simant:673A` | 1 | 1 | 0 | 1 | [simant_673A.json](simant_673A.json) |
| `simant:6A38` | 55 | 53 | 2 | 8 | [simant_6A38.json](simant_6A38.json) |
| `simant:8A76` | 32 | 31 | 1 | 5 | [simant_8A76.json](simant_8A76.json) |
| `simant:9D04` | 33 | 31 | 2 | 9 | [simant_9D04.json](simant_9D04.json) |
| `simant:B324` | 25 | 23 | 2 | 12 | [simant_B324.json](simant_B324.json) |
| `simant:CF3A` | 3 | 3 | 0 | 1 | [simant_CF3A.json](simant_CF3A.json) |
| `simant:D3E2` | 1 | 1 | 0 | 1 | [simant_D3E2.json](simant_D3E2.json) |
| `simant:D6DC` | 10 | 9 | 1 | 1 | [simant_D6DC.json](simant_D6DC.json) |
| `gr:0000` | 9 | 9 | 0 | 2 | [gr_0000.json](gr_0000.json) |
| `gr:08F4` | 2 | 2 | 0 | 1 | [gr_08F4.json](gr_08F4.json) |
| `gr:364C` | 1 | 1 | 0 | 1 | [gr_364C.json](gr_364C.json) |
| `gr:4A2C` | 1 | 1 | 0 | 1 | [gr_4A2C.json](gr_4A2C.json) |
| `gr:4C36` | 1 | 1 | 0 | 2 | [gr_4C36.json](gr_4C36.json) |
| `gr:514C` | 1 | 0 | 1 | 1 | [gr_514C.json](gr_514C.json) |
| `gr:59E4` | 1 | 0 | 1 | 1 | [gr_59E4.json](gr_59E4.json) |
| `gr:6410` | 2 | 0 | 2 | 8 | [gr_6410.json](gr_6410.json) |
| `gr:7712` | 3 | 2 | 1 | 13 | [gr_7712.json](gr_7712.json) |
| `antedit:00F4` | 131 | 109 | 22 | 18 | [antedit_00F4.json](antedit_00F4.json) |
| `antedit:67C6` | 11 | 5 | 6 | 3 | [antedit_67C6.json](antedit_67C6.json) |
| `antedit:6E72` | 1 | 1 | 0 | 1 | [antedit_6E72.json](antedit_6E72.json) |
| `antedit:6EE2` | 4 | 4 | 0 | 1 | [antedit_6EE2.json](antedit_6EE2.json) |
| `antedit:7022` | 19 | 17 | 2 | 6 | [antedit_7022.json](antedit_7022.json) |
| `antedit:9248` | 19 | 18 | 1 | 6 | [antedit_9248.json](antedit_9248.json) |
| `antedit:A4BC` | 37 | 27 | 10 | 10 | [antedit_A4BC.json](antedit_A4BC.json) |
| `antedit:C19C` | 27 | 23 | 4 | 6 | [antedit_C19C.json](antedit_C19C.json) |
| `antedit:DC1E` | 3 | 2 | 1 | 1 | [antedit_DC1E.json](antedit_DC1E.json) |
| `antedit:E100` | 13 | 13 | 0 | 2 | [antedit_E100.json](antedit_E100.json) |
| `simone:04DE` | 17 | 16 | 1 | 9 | [simone_04DE.json](simone_04DE.json) |
| `simone:1414` | 2 | 1 | 1 | 1 | [simone_1414.json](simone_1414.json) |
| `simone:16AE` | 19 | 18 | 1 | 9 | [simone_16AE.json](simone_16AE.json) |
| `simone:2B42` | 6 | 4 | 2 | 3 | [simone_2B42.json](simone_2B42.json) |
| `simone:3120` | 3 | 3 | 0 | 12 | [simone_3120.json](simone_3120.json) |
| `simone:4668` | 30 | 26 | 4 | 5 | [simone_4668.json](simone_4668.json) |
| `simone:5AD2` | 35 | 33 | 2 | 20 | [simone_5AD2.json](simone_5AD2.json) |
| `simant1:0000` | 40 | 37 | 3 | 14 | [simant1_0000.json](simant1_0000.json) |
| `simant1:2D4E` | 26 | 24 | 2 | 14 | [simant1_2D4E.json](simant1_2D4E.json) |
| `simant1:5344` | 21 | 19 | 2 | 13 | [simant1_5344.json](simant1_5344.json) |
| `simant1:75F4` | 37 | 34 | 3 | 11 | [simant1_75F4.json](simant1_75F4.json) |
| `simant1:9612` | 3 | 1 | 2 | 1 | [simant1_9612.json](simant1_9612.json) |
| `simant1:96D4` | 13 | 11 | 2 | 3 | [simant1_96D4.json](simant1_96D4.json) |
| `simtwo:0000` | 28 | 25 | 3 | 6 | [simtwo_0000.json](simtwo_0000.json) |
| `simtwo:1378` | 63 | 62 | 1 | 8 | [simtwo_1378.json](simtwo_1378.json) |
| `simtwo:3EF8` | 19 | 18 | 1 | 7 | [simtwo_3EF8.json](simtwo_3EF8.json) |
| `simtwo:4CDC` | 7 | 6 | 1 | 3 | [simtwo_4CDC.json](simtwo_4CDC.json) |
| `simtwo:5AB0` | 60 | 57 | 3 | 1 | [simtwo_5AB0.json](simtwo_5AB0.json) |
| `simtwo:6C5A` | 1 | 1 | 0 | 2 | [simtwo_6C5A.json](simtwo_6C5A.json) |
| `simtwo:78CA` | 17 | 15 | 2 | 3 | [simtwo_78CA.json](simtwo_78CA.json) |
| `simtwo:8176` | 1 | 1 | 0 | 1 | [simtwo_8176.json](simtwo_8176.json) |
| `simtwo:858A` | 1 | 1 | 0 | 3 | [simtwo_858A.json](simtwo_858A.json) |
| `simtwo:8BF0` | 1 | 1 | 0 | 5 | [simtwo_8BF0.json](simtwo_8BF0.json) |
| `simtwo:9A86` | 2 | 1 | 1 | 7 | [simtwo_9A86.json](simtwo_9A86.json) |
| `simtwo:ADE0` | 3 | 3 | 0 | 1 | [simtwo_ADE0.json](simtwo_ADE0.json) |
| `simtwo:B300` | 1 | 1 | 0 | 1 | [simtwo_B300.json](simtwo_B300.json) |
| `simtwo:B702` | 1 | 1 | 0 | 1 | [simtwo_B702.json](simtwo_B702.json) |
| `simtwo:BB96` | 1 | 1 | 0 | 1 | [simtwo_BB96.json](simtwo_BB96.json) |
| `simtwo:C32E` | 8 | 7 | 1 | 14 | [simtwo_C32E.json](simtwo_C32E.json) |
| `simtwo:E4E8` | 2 | 2 | 0 | 4 | [simtwo_E4E8.json](simtwo_E4E8.json) |
| `text:534E` | 2 | 0 | 2 | 6 | [text_534E.json](text_534E.json) |
| `text:67DE` | 16 | 14 | 2 | 1 | [text_67DE.json](text_67DE.json) |
| `text:7D3E` | 1 | 1 | 0 | 4 | [text_7D3E.json](text_7D3E.json) |
