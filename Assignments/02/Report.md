# Results for Assignment 02

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster. The values below refer to testing on the final dataset. Speedup refers to real time speedup.

| Version | Time (Real) | Time (User) | Time (Sys) | Speedup (Real) | Changes |
| :-----: | :-----: | :-----: | :-----: | :------: | ------- | 
| 01 | 11m1.077s | 10m51.699s | 0m3.613s | &mdash; | Initial Version - No Changes |
| 02 | 1m23.467s | 13m51.211s | 0m0.346s | 7.92x | Each thread calls getNext(number) and share a maxIter value and Records vector |
| 03 | 1m8.646s  | 11m24.040s | 0m0.014s | 9.63x | Each thread cals getNext(number) and have their own maxIter and Records vector |
| 04 | 1m9.739s  | &mdash;    | &mdash;  | 9.48x | This is from version 04b4 - See notes below for implementation notes |
| 05 | 1m56.465s | 18m33.869  | 0m0.849s | 5.68x | Each thread has different batch sizes 1, 2, 4, 8, ... , 512 |

## Notes
1. All times where obtained through testing on blue at roughly the same time of day
   on the same day.
2. The User and Sys times have been lost for version 04, and that code has been lost. 
   Since it is not the final submitted version, I have omitted those values. Though,
   I can re-write that code to get those times if desired.
3. The final submitted version is 03.


## 04a Tests
The following are testing values for version 04a.
In this, batch sizes are regularly divided by 2 after every BatchIters
where each batch means processing a vector of size BatchSize numbers.

| Version | Time (Real) | Init. BatchSize | BatchIters |
|:-----:  |:-----: | :-----: | :-----: |
| 04a1 | 1m25.681s | 512 | 10 |
| 04a1 | 1m25.633s | 1024 | 4 |


## 04b Tests
The following are testing values for version 04b.
In this, the batch size is decremented after every batch by the
decrement value.
| Version | Time (Real) | Init. BatchSize | Decrement Value |
|:-----:  |:-----: | :-----: | :-----: |
| 04b1 | 1m10.596s | 512 | 1 |
| 04b2 | 1m17.574s | 512 | 10 |
| 04b3 | 1m11.549s | 256 | 1 |
| 04b4 | 1m9.739s  | 128 | 1 |
| 04b5 | 1m48.160s | 64  | 1 |

## 04c Tests
The following are testing values for version 04c.
In this, batch sizes are static and are the same for each thread.

| Version | Time (Real) | Init. BatchSize |
|:-----:  |:-----: | :-----: |
| 04c1 | 1m40.051s | 64 | 
| 04c2 | 2m5.946s  | 128 |
| 04c3 | 1m42.444s | 256 |
| 04c4 | 1m43.197s | 512 |
| 04c5 | 1m42.142s | 1024 |
