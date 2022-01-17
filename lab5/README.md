# Lab5 -  Page Replacement Simulation: LRU and LFU
Check whether or a new reference is a hit or a miss

## Requirements
-    Page lookup
        -    Check whether or a new reference is a hit or a miss
        -    Hash tables, binary search trees, skip lists….
-    Victim selection
1.    LFU
        -    The least frequently used page
        -    If two pages have the same access count, the page having a smaller reference sequence number is replaced
        -    You may need to store the reference sequence number when a page is added to the page cache
![](https://i.imgur.com/1pxgEdE.png)

![](https://i.imgur.com/R6elCyl.png)

2. LRU
    -    The least recently used page
![](https://i.imgur.com/zB4tIUc.png)
![](https://i.imgur.com/Q21bXYj.png)

## Procedure
1. Algorithm=LFU
2. For (frame # = 128, 256, 512, and 1024) do
    -    Read the trace file
    -    Run simulation
    -    Print out the hit count, miss count, page fault ratio
3. Print out the total elapsed time of Step 2
4. Algorithm=LRU
5. For (frame # = 128, 256, 512, and 1024) do
    -    Read the trace file
    -    Run simulation
    -    Print out the hit count, miss count, page fault ratio
6. Print out the total elapsed time of Step 5
## Hints
-    here we do not simulate working set migration, so LFU slightly outperforms LRU; but in real life workloads, LRU usually slightly outperforms LFU

## Test Cases
**Input:**
-    Format of “sample.txt”:
```
<Unsigned integer>\n
<Unsigned integer>\n
<Unsigned integer>\n
<Unsigned integer>\n
```
-    Total request # <= 500 millions
-    Total frame # <= 8192
-    For each iteration, you should open the file, run the
simulation, print the result and close the file

**Output:**
![](https://i.imgur.com/odyRSaz.png)

Testing OS Environment
-    Ubuntu 16.04, Ubuntu 14.04 


## Run command
```
g++ -std=c++11 0516222_5.cpp -o a.out
./a.out sample.txt
```

## Result
![image](https://github.com/becca211137/operating_system/blob/master/lab5/result.png)
