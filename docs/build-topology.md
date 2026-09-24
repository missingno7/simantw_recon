# Probable historical build architecture of SIMANTW.EXE

This report records what the executable itself preserves about how the original
project was organised: named code groups, translation units / object members,
and the order in which LINK consumed them. It is routing evidence for the
recovery factory, not recovery credit. Machine-readable results:
`evidence/topology/build-topology.json` (regenerate with
`python tools/build_topology.py`), unit tables in
[build-topology-units.md](build-topology-units.md), linker experiments under
`evidence/experiments/toolchain/link-layout/`.

Three levels are kept apart throughout:

| Level | Meaning here | Recoverable from the EXE? |
| --- | --- | --- |
| A. Code group | A named physical NE code segment (`SIMANT_MODULE`, …) | Yes, directly (MAPSYM names, NE segment table) |
| B. Translation unit / object member | One `.C` file compiled to one `.OBJ`: a contiguous code contribution, a private CONST selector pool, private `_DATA`/`_BSS` | Partly: same-object membership is provable, most exact boundaries are not |
| C. Build component / static library | Which objects were linked explicitly and which were pulled from libraries | Only the explicit-versus-library distinction and the pull order |

## 1. The code-group names are deliberate

MSC C/C++ 7.00 names a code segment `<basename>_TEXT` by default; the compile
service's `INPUT.C` produces `INPUT_TEXT`
(`evidence/experiments/toolchain/link-layout/PACK.MAP`). The six game groups
`SIMANT_MODULE`, `GR_MODULE`, `ANTEDIT_MODULE`, `SIMONE_MODULE`,
`SIMANT1_MODULE`, `SIMTWO_MODULE` therefore come from an explicit `/NT<name>`
(or an equivalent makefile policy) applied per source file; the runtime and a
third-party profiler stub keep the default `_TEXT`. They are not linker
inventions: LINK 5.30 merely combines same-named logical segments.

LINK 5.30 behaviour established with the pinned linker (nine tiny objects, a
library, `/PACKCODE` on and off, a `.DEF` `SEGMENTS` list):

- logical segments are ordered by the `SEGMENTS` statements first, then by first
  occurrence in link order; `/PACKCODE` packs adjacent logical code segments into
  one physical segment;
- inside one logical segment every object's contribution is appended in link
  order; explicit objects precede library members; library members are pulled in
  library member order, not reference order;
- DGROUP classes (`_DATA`, `CONST`, `_BSS`) are likewise filled in link order.

## 2. What the DGROUP layout records

MSC 7 keeps far-object selectors in a private CONST word table per object,
allocated in code-generation order (verified: reordering `extern` declarations
does not change the pool; index expressions are allocated before their array
base). Every `mov es,[word]` in the game therefore points into its own object's
pool. The pool region is one dense run of selector-relocated, unnamed DGROUP
words, `BE6E`–`C6DE` (1074 words), followed by the C runtime's CONST
(`__caption` at `C6E8`). Two hard facts follow and were checked on all 1065
game functions:

1. **Sharing proves one object.** 0 pool words are shared across code groups
   (falsification test); 55 multi-function same-object components emerge from
   sharing alone, before any name is looked at. Admitted private `_DATA`/CONST
   contributions add the same kind of proof (e.g. the three `db_*` functions on
   `_DATA` 45941).
2. **Positions record link order.** Pool words and private `_DATA` grow in link
   order, so a foreign code group's words between two functions of one group
   prove an object boundary, and a later function whose object sits *earlier*
   in the pool than a previous function's object proves two logical segments.

Not usable as evidence: within one proven object the pool order deviates from
code order at function granularity (`DoUserButtonUpdate` uses `BE70`,
`UpdateUserButtons` introduces `BE6E`; `win_DrawMapWindow` introduces `C1EE`
below `DrawMapCursor`'s `C1F0`) — allocation follows the compiler's evaluation
order, not final code order. Reversals without foreign words in between are
therefore recorded (`observed_reversals`) but neither join nor cut.

Positive controls: every previously supported joint unit (menu state, dialog
tables, map stencils, yard state, sound availability) falls inside one derived
component.

## 3. Link order of the units (global, from pool positions)

```
BE6E SIMANT   main window/buttons/bookmarks .. WINMAIN, palette, menu, score/dialogs, edit/yellow help
BF74 GR       hanim_* animation                     (explicit object, early)
BF78 GR       IsMMMidiAvail .. myServiceSong        (multimedia, 28 functions, one pool word family)
BF7E ANTEDIT  OverlayTileSet .. ResetEditScrollRange (edit window, spider, balloons, scroll)
C084 SIMANT   history, EditMessage, yard/map controls, AddSomeAnts .. MysteryButton, InitTriVars .. initControls, About, Intro, NewGame
C16A GR       font_SetFont .. font_PrintStr
C170 ANTEDIT  OPENDLG .. ClearLastFileName          (file dialogs / load-save)
C196 ANTEDIT  yard event, DrawYardCursor .. YardArea (yard)
C1E0 ANTEDIT  InitMapFunctions .. Mini_DrawMapI, tools menus, MapAreaEvent .. ToggleMiniMapCursor (map, minimap)
C238 ANTEDIT  EditToolsMenu .. SetExpTool, warn/health/exp menus, processExp .. SetSM (experimental tools, terrain)
C288 GR       MakeBalloon
C2AC SIMONE   initStuff .., CountAnts .. PlaceEggR, GetEnterDirB/R, TryAntTheme
C2FE SIMANT1  DoAntSim .. IsItFood            (shared ant simulation, 31)
C34E SIMANT1  DoAntSimB .. GetOutB            (black colony, 30)
C382 SIMANT1  DoAntSimR .. GetOutR            (red colony, 28)
C3AC SIMANT1  DoAntMoveY .. GetMyDir          (yellow/player ant, 15)
C3FC SIMONE   DigMyNewHole .. DigTileThemR, FixExitMap, list management, house/yard patches, spider
C472 SIMANT1  GetSmellT
C478 SIMONE   IsClear3x3 .. TryMyDropOrLift   (48)
C4BE SIMTWO   GetStrategy .. GetRedDefendDir, InitSimYard .. GetNearbyPatches, sow/ant lions, pillar, InitSimVars, RandWorld .. AddFood, AddBlack/RedAnts
C62E SIMANT1  MakeRedInitiator .. GetRedBestDirs   (linked after the SIMTWO simulation objects)
C64C SIMTWO   goStep* / Finish*Step, Overlay*Tiles, Feedback .. LessonDone
---- C runtime members (crt0dat, output, …) occupy _DATA 44240–45538 ----
C686 SIMTWO   db_* object database, DB* records, OpenDB/CloseDB, index functions, Encode, font_MakeImage
C69C GR       SetHelpCursor .. IBMInitStuff, ReadConfig, fonts, GPutStr, DoMonoBitmap, capture, ButtonHeld, ConvColor, menu state, ms_PopUpMenuResource
C6C4 SIMTWO   gr_JustifyStrInRect, win_RectFill, win_DrawObjectI, win_DrawWindow, win_LoadAllWindows .. win_DoProxMenu, win_GetVal ..
---- runtime CONST (__caption) ----
```

Three consequences are structural evidence, not interpretation:

- **Library-pulled units (level C).** The `db_*`/index/pack objects, the GR
  primitives head and the whole `win_*` framework contribute `_DATA` only after
  the C runtime's first members (`_db_numOfHandles` 45542, `_egaPaletteFlag`
  47662, `_winObjStr` 47900, `_win_hwnd` 48294 …) and CONST only after every
  explicit game object. Explicit objects cannot follow library members, so
  these units were linked from libraries (or after the runtime library on the
  command line, which LINK treats the same way). Their order — database, cache,
  pack/unpack, graphics primitives, window framework, then the remaining
  runtime members (`__fmode`, `__fpinit`) — is the order in which references
  were resolved. The EXE does not say whether they came from one `.LIB` or
  several; "WIN.LIB containing WINOBJ.OBJ" versus "WINOBJ.OBJ after the CRT
  library" is not distinguishable here.
- **GR_MODULE and ANTEDIT_MODULE contain more than one logical segment.** In GR
  the code order is [primitives head][mem/Ralloc][MakeBalloon][fonts][printf,
  hanim][multimedia] while the link order is hanim, mm, fonts, MakeBalloon,
  …, primitives (verified by admitted `_DATA` placements: `_GCloseFonts`
  47709 versus `_RallocInfo` 2150). With a single logical segment that is
  impossible; the physical segment must have been packed from several logical
  code segments ordered by a `.DEF` `SEGMENTS` list or by first occurrence.
  ANTEDIT shows the same signature (experimental tools `C238`–`C282` precede the
  file/yard/map units `C170`–`C236` in code but follow them in the link). The
  `.SYM` file keeps only the first logical name per physical segment, so the
  other names are lost.
- **SIMANT, SIMONE, SIMANT1 and SIMTWO behave as single logical segments**: code
  order equals link order everywhere the evidence reaches.

## 4. Candidate units and their confidence

The derived units are in [build-topology-units.md](build-topology-units.md):
ranges between proven boundaries (`CANDIDATE_RANGE`), same-object components
inside them (proof by shared pool/private words plus contiguity), and
`UNLOCATED` stretches without any DGROUP evidence. Only components carry
`same object` proof; a range may still hold several objects. No unit is
`CONFIRMED_TU`: exact object boundaries need original-object provenance the EXE
does not contain. Examples of what the components show without names:

| Component | Functions | Proof | Reading |
| --- | --- | --- | --- |
| simant1:0000 / 2D4E / 5344 / 75F4 | 31 / 30 / 28 / 15 | 86 / 81 / 76 / 45 shared-slot joins | the shared, black, red and yellow ant simulation files, exactly the A/B/R/Y public-name sequence |
| gr:7712 | 28 | 17 slot joins + `_DATA` 3242 | one multimedia object around selector `BF78`/`SIMANT_DATA_GROUP`; `hanim_*` (`BF74`) is a separate, adjacent object |
| simtwo:4CDC | 9 | 16 slot joins | the pillar object (`DoPillar` introduces all seven words `C59A`–`C5A6`) |
| simtwo:6EFE | 11 | 55 slot joins + 2 private words | the goStep/Finish*Step movement object; assembled and admitted in two units |
| simtwo:C806 | 24 | 3 slot joins | `win_LoadAllWindows .. win_DoProxMenu`, the window framework core |
| antedit:00F4 | 40 | 42 joins + private word | edit window, spider rendering, balloons and scrolling are one object |

Ten unnamed code regions (4577 bytes) sit between publics: static helper
functions of their units (edit: 694 and 1522 bytes; map: 781 and 1151;
pack/unpack: 150/106/65/41; a 58-byte unnamed gap after `_MemRChr` at
SIMTWO:F795-F7CE with no proved caller or identity; `font_MakeImage`: 9).
A unit that contains one cannot be assembled from its publics alone.

Known rejected groupings are preserved: the four PACK selector-pool placement
conflicts (`FollowCatDir`, `SendBoyMsg`, `StartAttack`, `SetAntLion`),
`ClrModePop`'s named-based externs, `InitSpider`'s nonzero form, and the
six-function goStep/Finish attempt (skipping `goStepNE..FinishDiagStep` breaks
public placement: a composed unit must be a contiguous run).

## 5. Optimizer profiles along the boundaries

Probes of the preserved best candidate under every catalog profile
(`evidence/experiments/optimizer-profile/probes/`) give strict results only
for a few functions; each attaches to its component, not to itself:

| Function | Profile | Component | Result |
| --- | --- | --- | --- |
| `_SeparateFile` | og | antedit:9248 neighbourhood (file dialogs) | CONFIRMED_MEMBER, admitted |
| `_SpecialTutorialInit` | og | antedit:9248 (OPENDLG .. ClearLastFileName) | strict |
| `_IsPillDead` | og | simtwo:4CDC (pillar) | STRONGLY_SUPPORTED_MEMBER, admitted |
| `_RecruitRed` | og | simtwo:0000 (GetStrategy .. GetRedDefendDir) | strict |
| `INDIRECTDLGPROC` | ga | simtwo:C806 (window framework) | strict: the exported-prologue evidence |
| `_win_SetColorFromObj` | refutes og | simtwo:B442 (colour helpers, before the framework core) | admitted only under baseline |

So the `/Og` counterexample and the `/GA` evidence live in different components
of the same code group: the colour helpers (`win_SetColorNum`,
`win_SetColorFromObj`, `win_SetColorFromObjNum`, pool `C6C4`) precede the
framework core (`C6CC`–`C6DC`) with no proven boundary between them but no
proven join either. The model "WINCOLOR → profile A, WINDRAW/WINGROUP → profile
B" is consistent with the evidence and not yet proven; the catalog therefore
assigns `ga` to `simtwo:C806` only and keeps the colour component on baseline.
Diagnostic-only gains under `/Og` cluster in the SIMTWO simulation ranges and in
ANTEDIT; none appears in the library-pulled units, which is what a separately
built library would look like.

## 6. Implications for the factory

- Profile assignments attach to components (`layout/compiler-profiles.json`),
  and a grinder packet inherits its unit's profile and rules.
- Unit assembly (`tools/tu_assembly.py propose`) works on components: a group
  must be a contiguous run of publics whose predicted pool block is contiguous
  and in order; missing introducers and static helpers are reported per blocked
  function (`evidence/recovery/parked-reclassification.json`).
- A private uninitialised static may only be placed inside the original BSS
  region; four earlier admissions had bound `win_hwnd[]` slots and an
  initialised tile mask as private BSS and were re-admitted with the real
  declarations.
- The remaining ambiguities: exact object boundaries inside every range,
  the second logical segment names of GR and ANTEDIT, and the library
  partition of the late-linked units.
