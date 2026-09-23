# FloodNestB loop lifetime variants

Five semantically equivalent nested loop forms were compiled: nested `for`, nested `while`, outer `for` with inner `do/while`, outer `do/while` with inner `for`, and nested `do/while`. All five collapsed to one OMF object (`770fe47da6cc...`) with the same 60-byte body, 27/27 opcode matches, 1/1 `_MapB` fixup, and seven register-only differences.

The tested loop-control forms do not control the remaining schedule under the assigned baseline profile. These results do not establish a general MSC7 rule. The spec, candidates, receipts, and compact comparison are preserved here.
