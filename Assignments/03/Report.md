# Results for Assignment 03

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.

| Version |   Time  | Speedup  | Changes |
| :-----: | :-----: | :------: | ------- |
| 01 | 23.16s | &mdash; | Initial Version - No Changes |
| 02 | 14.61s | 1.59x | Basic Threading - Launch a thread for each session - No Synchronization |
| 03 | 18.65s | 1.24x | Single Producer, Single Consumer, Basic Ring Buffer |
| 04 | 18.93s | 1.22x | Multiple Producers, Single Consumer - No Async |
| 05 | 18.58s | 1.25x | Basic Async Threading |
| 06 | 19.02s | 1.22x | Single Producer, Single Consumer, Basic Ring Buffer, Asynch prod/consumer calls |
| 07 | 19.38s | 1.20x | Multiple Producers, Single Consumer, With Consumer Async |



## Notes
1. All times where obtained through testing on blue, one after another on the same network.
2. I don't have a particular favorite final version, but version 03 is the one that will appear
as server.cpp
3. I wrote version 02 as a joke but I am astonished that it did so much better than every other version.
