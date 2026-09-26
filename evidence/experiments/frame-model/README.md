# MSC C 7.00 frame-home and register-allocation model

This experiment uses the 415-function `/Zi` CodeView frame corpus in `build/supervisor/frames.json`. CodeView homes and register records are the ground truth; the admitted binaries were compiled with `/Zi`, which the supervisor verified leaves code bytes unchanged. All source-derived features and scratch probes live under `build/workers/slot-model/`.

## Rules found

**BP home order.** For the corpus-wide default, declaration order is the strongest exact-order rule. The source-aware model preserves that default and applies the controlled address-only rule when all homes in a frame are address-taken: smaller objects first, then more static references, then first use; most recent store resolves some remaining ties. The reference count is lexical, so a use inside a loop counts once. In mixed frames the class boundary and spill order remain uncertain.

The 56 controlled snippets reproduce those address-taking effects: equal-count ties follow first use even when declarations are reversed; raising one local's static reference count moves it nearer BP; a later store wins selected ties; changing only identifier spellings does not change slots; `char` homes pack at `BP-1`/`BP-2`; then the word and long homes occupy `BP-4` and `BP-8`. The snippets and all three profile outcomes are embedded in `results.json`.

**SI/DI candidates.** The source-visible eligibility screen is a two-byte word scalar or near pointer that is neither volatile nor address-taken. It covers 203 of the 205 `S_REGISTER` records; the two exceptions are far/aggregate pointer records. The 205 records use CV register IDs SI 95, DI 63, CX 21, DX 15, BX 11. Thus 47 records are in other registers and do not fit an SI/DI-only allocation model.

Among eligible locals, read/write activity and static references improve ranking over declaration order, but they do not determine the winners. `slotmodel.py` ranks by reads+writes, static references inside loops, then first use. With the observed per-function SI/DI capacity supplied to isolate local priority, its held-out score is 44/82 matching assignment labels (53.7%); it matches the SI choice in 34/50 frames (68%), the DI choice in 10/29 (34.5%), and both in 10/21 frames containing both (47.6%). Capacity itself is not predicted.

The separate rank-only experiment lets each candidate rule select the observed number of all `S_REGISTER` records, including CX/DX/BX. The rule selected on training (last-use order) falls to 55.4% winner recall, 33.3% SI-first accuracy, and 9.5% exact SI-then-DI assignment on held-out candidate frames. The strongest held-out rule happens to be loop-reference count (67.4% winner recall and 57.1% exact SI-then-DI), but it was not selected by the training criterion. This split instability is evidence that the compiler's promotion decision, register capacity, and assignment order depend on flow analysis or allocator state that these local features do not capture.

Controlled probes show why: equally referenced straight-line locals stay homed, while adding branches or loop-carried updates changes which variables receive registers. The 56 cases produce identical home/register records under `/Oelw`, `/Oeglw`, and `/Oegilw`, so these local probes do not distinguish those optimization profiles.

## Held-out validation

Functions are split by a SHA-256 bit of their C source path, keeping all functions from one source together. This yields 64 training and 73 held-out multi-home functions; across the complete corpus the split is 197/218 functions and 105/100 `S_REGISTER` records.

| Rule | Train exact order | Held-out exact order | Held-out pairwise |
|---|---:|---:|---:|
| Declaration order (selected on training for exact order) | 40/64 | 42/73 | 200/308 = 64.9% |
| Loop-contained static references, then total references (selected on training for pairwise) | 33/64 | 34/73 | 211/308 = 68.5% |
| Uses descending, first use | 28/64 | 29/73 | 180/308 = 58.4% |

Per-class fitting selected uses/first-use for address-taken pairs and loop-contained references/total references for word scalars. On held-out pairs, these score 9/11 (81.8%) and 129/173 (74.6%), respectively. There are few long/aggregate/char comparisons, and class-specific training overfits those groups. See `results.json` for every candidate rule, every local-class pair score, homogeneous-frame exact scores, and split counts.

The included `slotmodel.py` predicts home order and estimates BP offsets. On held-out multi-home functions, its order is exact for 42/73 (57.5%) with 200/308 (64.9%) pairwise accuracy. Among records with known object sizes, it predicts 71/168 BP offsets (42.3%); all known offsets match in 22/67 frames (32.8%). This gap shows that source order and local type alone do not recover exact offset placement, especially where scopes reuse storage or CodeView gives no aggregate size.

## Reproduction and limits

From the repository root:

```powershell
python build/workers/slot-model/probes.py
python build/workers/slot-model/score_model.py
python build/workers/slot-model/write_results.py
```

`probes.py` compiles every snippet with MSC 7.00 `/Zi` under baseline, `og`, and `ogi`, then reads CodeView `S_BPREL16` and `S_REGISTER` records. `score_model.py` scores the module against `frames.json`; `write_results.py` writes this report's machine-readable `results.json`.

This is an empirical guide, not an exact replacement for MSC's optimizer. The local eligibility rule is strong, address-only slot order is reproducible, and the word-scalar home/register rankings are useful priors. Exact register promotion, mixed-class stack allocation, all BP offsets, and register identity still depend on compiler flow analysis or hidden allocator state.
