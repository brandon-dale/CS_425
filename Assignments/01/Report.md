# Results for Assignment 01

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Memory (KB) | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| 01 | 9.64s | &mdash; | 1041328 | Initial Version - No Changes |
| 02 | 2.06s | 4.68x | 1044024 | Compiled with the -Ofast flag |
| 03 | 2.25s | 4.28x | 1040948 | Compiled with the -O3 flag |
| 04 | 2.26s | 4.27x | 1040460 | Compiled with the -O2 flag |
| 05 | 3.36s | 2.87x | 1041232 | Compiled with the -O1 flag |
| 06 | 3.80s | 2.54x | 1041328 | Compiled with the -Os flag |
| 07 | 9.94s | 0.97x | 1040760 | Use reciprocals instead of divisions |


## Notes
1. All times where obtained through testing on blue.
