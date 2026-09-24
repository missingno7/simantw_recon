# DoBitmap palette selector evidence

Target: `GR_MODULE:_DoBitmap`, 678-byte CFG extent, assigned baseline `/AL /G2 /Gs /Oelw /NTGR_MODULE`.

## Owner and meaning of SS:BA2E

- `factory-packet.json` disassembles the word read at function offset `0x1e7` as `cmp word ptr ss:[0xba2e], 0`.
- At `0x1e4`, the function first loads DS from the locked `BITMAPINFO` selector home (`[bp-4]`). The SS override therefore keeps the subsequent global read in the preserved stack/DGROUP segment while DS addresses the locked info block.
- `evidence/symbols/symbol-address-map.json` maps `000a:ba2e` to `_egaPaletteFlag`. `evidence/symbols/inventory.json` records segment 10 / DGROUP, offset `0xba2e` (47662), and next symbol at `0xba30`; it does not prove a data extent or source type.
- The target branches on this word independently of the `convert` parameter: nonzero falls through to the Dx8 table accesses rooted at `0x8c00` (bytes at `+2`, `+1`, `+0`); zero jumps to the accesses rooted at `0x8c40` (four-byte entry with a zero fourth byte). The exact semantic observation supported here is that `_egaPaletteFlag` selects the palette-copy path.
- The later `push ss; pop ds` at function offset `0x236` restores the DGROUP data segment before the subsequent `_clipDC` access at `0xcf52`.

## Related admitted bitmap evidence

- `src/recovered/BitmapImageSize.c` provides the DWORD-padded DIB image-size formula.
- `src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c` establishes a 40-byte BITMAPINFOHEADER followed by a palette and a `SetDIBitsToDevice` call; its palette is explicitly written as RGB/reserved bytes.
- These sources support the DIB layout but do not independently define `_egaPaletteFlag` or the two color tables.

## Strict attempt

Attempt 02 revised the previous readable candidate to use `extern int near egaPaletteFlag` and branch on it independently from `convert`. Result: `NO_COMPLETE_MATCH`, 678-byte target vs 590-byte candidate, 161/257 opcode matches, score 0.463035. The diagnostic reports control-flow, local-frame, memory/fixup, and private `_DATA` placement differences. Prior attempt 01 remains archived unchanged.

## Next experiment

Restructure the color-table emission as two separate loops keyed by `egaPaletteFlag`, matching the target's observed channel stores: the nonzero path reads bytes from `Dx8 + 0x8c00` in reverse channel order (`+2`, `+1`, `+0`) and advances by four; the zero path reads from `Dx8 + 0x8c40`, writes three table bytes plus a zero reserved byte, and advances by four. Keep this selector independent from the `convert` branch, then strict-test once against the same assigned profile.
