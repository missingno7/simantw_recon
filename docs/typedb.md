# Declaration database

`python tools/typedb.py build` parses the admitted C files named by `src/recovery.json` with pycparser 3.00 and the permuter's MSC dialect adapter. It records each distinct declaration used by an admitted member body, a majority canonical form, per-source variants, conflicts, and the needed typedef/struct definitions. Scaffold-reference comments, stand-in functions, and names used only by `POOLSTUB_TEXT` bodies are excluded. A TU-specific form remains a supported variant even when it differs from the majority.

`python tools/typedb.py check draft.c` reports hard conflicts with verified forms and soft conflicts with machine evidence for names without verified declarations. Machine evidence comes from the locked NE/MAPSYM pair and symbolized disassembly whose instruction bytes are checked against the NE segments; it summarizes access widths, sign or zero extension, branch signedness, far loads, strides, parameter accesses, calls, argument cleanup, and return use. It is diagnostic and does not replace source evidence.

`python tools/typedb.py resync draft.c -o out.c` rewrites conflicting file-scope declarations toward the verified majority and inserts missing type definitions. It preserves function body text exactly. A source form already verified for that admitted TU is left intact, including legitimate near/far or incomplete-array views. The tool writes only its requested output; the normal strict compiler/member comparison remains the proof step.

For open drafts, resync also keeps a declaration view when the body requires an array, an assignable scalar, pointer arithmetic, a matching struct field, parameter name, or call arity that the majority form cannot support. When admitted variants provide a struct layout whose fields match the body, it can select that verified view. These constraints can leave a canonical mismatch in `check`; the report distinguishes such body-compatible views from declarations that were rewritten.

Focused tests: `python -m pytest -q tests/test_typedb.py`.
