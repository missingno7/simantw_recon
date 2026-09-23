# `_DoFastBitmap` isolated research

Production job `DoFastBitmap-e1a0ad76d1` exhausted its eight strict attempts. It remains unpromoted; this note records the bounded arithmetic and selector findings only.

## Positive arithmetic evidence

`attempt01/candidate0000.c` uses:

```c
info->imageSize = ((((long)width * 4L) + 31L) / 32L) * (long)height * 4L;
```

Its strict diff aligns with the target's complete row-stride sequence at `+0x8f..+0xb0`: two left shifts with carry, add `0x1f`, `__aFldiv`, `__aFlmul`, then two more shifts with carry. Both helper-call sites align; the first structural mismatch is later, at buffer setup (`+0xe2`). This confirms the target-specific arithmetic form without claiming whole-member recovery.

## Negative Dx8 selector experiment

`isolated-dx8-source.c` was compiled once directly through the baseline MSC 7.00 compiler service, outside the capped production workflow. Its object is preserved as `isolated-dx8-pointer.obj` (873 bytes, SHA-256 `eb36220381b23c0f5a3543448cc22935909e47134dcfe6b66124e29ec5ddd62d`).

The experiment assigned `Dx8` to a plain far-pointer local, then read through that pointer. The OMF still contains seven `_Dx8` offset fixups at code offsets 246, 255, 273, 288, 309, 327, and 342. The target packet instead shows two `_Dx8` selector loads at function offsets `+0x102` and `+0x11e`, followed by indexed `ES:[DI+disp]` reads. A plain far-pointer alias therefore does not preserve the target's selector/index addressing through C7 optimization.

The isolated compile was not strict-tested or admitted and earns no recovery credit. The next useful discriminator is a source idiom that preserves the far pointer as an independently held value across optimization, or new unit evidence explaining the target's split selector loading.
