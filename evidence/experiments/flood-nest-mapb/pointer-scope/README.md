# FloodNestB pointer-scope discriminator

This three-candidate isolated MSC7 `/AL /G2 /Gs /Oelw /NTSIMONE_MODULE` batch kept the corrected near `_MapB` binding, loop/index expressions, and saved `int value` fixed. It compared function-scope `p`, inner-loop-scope `p` assigned after declaration, and inner-loop-scope `p` initialized at declaration.

All three compiled to one effective OMF class (`770fe47da6cc9e6c3ff270ea3f917de1b18a507856f12e61e62d2ca86e2c1a70`). The function remains 60 bytes with 27/27 aligned opcodes, the exact 1/1 `_MapB` fixup, and seven register-only differences. The target uses DI/BX where this class uses CX/DI. Thus these tested pointer lifetime and initialization forms do not control the remaining schedule under this profile.

Sources, compile receipts, and class-level compiler response are preserved in `trial/`, `results.json`, and `compact.json`. This is bounded negative evidence for these source forms only, not a universal MSC7 rule. No production state was changed.
