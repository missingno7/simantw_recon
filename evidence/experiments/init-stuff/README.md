# initStuff source recovery

After `PrepareStrings` was admitted, the live `_initStuff` packet showed the
same eighteen resource loads and far stores as its opening 433 bytes. The two
functions are adjacent in `SIMONE_MODULE`. `build_candidate.py` copied the
readable statements, changed the function name, and added only the observed
startup tail. The tail loads resource 1000, handles the failure message, locks
its table, initializes windows and simulation state, then sets the cursor.

The target failure path pushes `[bp-2]` without an earlier store in the
function. The candidate names that local `resourceError` and leaves it
uninitialized; this is an observed code fact, not a claim about intended
behavior. The candidate includes the exact target string literals from
DGROUP offsets 226A and 2293.

One production test reported `EXACT_CANDIDATE`: 576/576 target body bytes,
195/195 aligned opcodes, and 109/109 semantic fixups. The immutable candidate
under `evidence/recovery/workflow/jobs/initStuff-9712c2c2ff/attempt01/`
passed fresh independent promotion to `src/recovered/wf_initStuff-9712c2c2ff.c`.
The job's promotion proof is the recovery authority.
