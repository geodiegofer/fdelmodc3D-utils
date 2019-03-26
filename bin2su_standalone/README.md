```
```
# Template/files for SU-like C code

This template gathers SU's selfdoc (for printing out self-documentation), getpars (for robust parameter input via command-line), and 
SU-header structure.

`par.h` is a header for: `docpkge.c`, `getpars.c`, `atopkg.c` . It originally had extra functions/structures, which were edited out in order for this template to be self-contained.

`docpkg.c` has the self-documentation functions

`getpars.c` does parameter input with error checking, and requires functions from `atopkg.c`

`atopkg.c` is required by `getpars.c`, and have some useful printing functions (e.g. `warn`, `err`)

`segy.h` has the structure required to read/write SU headers (and is independent from the previous .c and .h).

Extracting these bits from the SU package in a self-contained manner was adapted from Jan Thorbecke's Correlation code (https://janth.home.xs4all.nl/HPCourse/index.html).



