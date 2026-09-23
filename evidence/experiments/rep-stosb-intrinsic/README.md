# MSC7 `memset` lowering for `_FillMapLegs`

This is isolated compiler research. It did not reopen the parked `_FillMapLegs`
production job or change the ordinary source-admission rule.

Under the assigned MSC 7.00 `/AL /G2 /Gs /Oelw /NTSIMONE_MODULE` profile,
`probe.py` compiled three small fixtures. An external `memset` call emitted no
`rep stosb`; source-local `#pragma intrinsic(memset)` emitted one `rep stosb`
in each of two fixture forms. Source, raw OMF, and compiler receipts are kept
beside `results.json`.

`fill-map-legs.py` then replaced the five byte runs of the best preserved
`_FillMapLegs` draft with intrinsic `memset` calls and ran the existing strict
grinder directly as a research probe. The candidate emitted exactly five
`rep stosb` instructions, matching that target *feature*, but the complete
member remained far from exact: 440 candidate bytes versus 503 target bytes,
105/206 aligned opcodes, 0/8 fixups, different frame and CFG. Full source,
receipt, diff, and strict result are in `fill-map-legs-run/`.

The experiment isolates one codegen mechanism without proving historical
source or unit context. A general pragma allowance is not justified by this
result; the current production job remains blocked. A future test would need
source evidence or a substantially closer body before a reviewed intrinsic
exception or production reissue is warranted.
