# UpdateEditIfBufInvalid same-TU negative control

The preserved attempt02 body calls public _DrawEdit. Direct target-card inspection shows the historical E8 EE 01 at ANTEDIT:14E3 resolves to the unnamed static helper at 16D4, not public _DrawEdit at 14EE. The target card calls list records the 16D4 near call; docs/grinder-lessons.md already warns about this helper.

A normal `tu_assembly build` with a source override excluded _UpdateEditIfBufInvalid because native body_exact is false. A reviewed full-unit research variant then inserted the preserved function beside admitted _DrawEdit and compiled once. The strict unit result was RULED_OUT_MEMBER: RUN4_TEXT public placements were inconsistent, with 86 candidate bytes for the two functions versus the historical 82-byte function followed by the one-byte _DrawEdit. Candidate call lowering stayed far (9A), whereas the target has a three-byte E8 to 16D4.

Artifacts: unit.c is the reviewed research variant; evidence/recovery/units/antedit_00F4_UpdateEditIfBufInvalid_2_reviewed/test/results.json is the strict comparison. The normal composer gate excluded the source-ineligible function; its generated output was discarded to preserve the older tracked unit artifact. No production job was reopened or credited. Next discriminating work requires source evidence for static helper 16D4.
