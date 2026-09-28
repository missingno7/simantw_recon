# LINK 5.30 far-data layout probe

Reproduce with `python evidence/experiments/commdata-layout/reproduce.py` from
the repository root. The script compiles the small C inputs in `sources/` with
MSC C/C++ 7.00 `/AL /G2 /Gs /Oelw`, then links eight combinations with the
locked LINK 5.30 runner. Its probe DEF retains the original executable model,
data/code attributes, `/PACKDATA`, and this exact `SEGMENTS` order:

```
SIMANT_MODULE, GR_MODULE, ANTEDIT_MODULE, _TEXT, SIMONE_MODULE,
SIMANT1_MODULE, SIMTWO_MODULE, SIMANT_DATA_GROUP, PACK, DGROUP
```

Exports and imports are omitted because the probe objects do not use them.
`layout-results.json` records compiler receipts and OMF segment classes,
initialized ranges and alignments, LINK maps, NE file lengths, minimum
allocations, and bytes present in each file-backed segment.

The distinction is material: explicitly initialized zero bytes are emitted;
private uninitialized `PACK FAR_DATA` placed inside a packed segment with an
initialized contribution is zero-filled inside that segment's file length;
FAR_BSS COMDEF and default `static far`/`huge` contributions extend minimum
allocation without extending that file length. `communals_reversed` changes
public offsets when object order is reversed; `nopackdata_contrast` keeps
PACK, INPUT5_DATA, and FAR_BSS in separate physical NE segments.
