# Lab4 - Merge Sort with a Thread Pool
Multithreaded sorting using a thread pool

## Requirements
1. Read data from the input file “input.txt”
2. n=1
3. Do the sorting with a thread pool of n threads
4. Print the execution time 
5. Write the sorted array to a file
    -    Filename: output_n.txt (e.g., output_3.txt if n=3)
6. n++; if n<=8 then goto 3

-    Reuse your assignment 3
-    The binding of jobs to threads must be dynamic
-    All threads in the thread pool must have been  created before the first job starts
-    A job is
        - Sorting a last-level array using bubble sort, or
        -    Merging two sorted sub-arrays into a large, sorted array
-    All the 8 output files must be identical
-    Execution time decreases as n increases
-    Performance improvement saturates as n increases

![](https://i.imgur.com/sejyvKk.png)

![](https://i.imgur.com/warrtCp.png)

## Hints
-    Initially, the dispatcher thread inserts eight sort  jobs for the eight bottom-level arrays and wakes up worker threads
-    The dispatcher checks if any two pairing (buddy) sub-arrays have been sorted. If so, it inserts a new job to merge the two sub-arrays

## Test Cases
**Input:**
-    Format of “input.txt”:
```
<# of elements of array><space>\n
<all elements separated by space>
```
**Output**
-    Output file format “output_?.txt”:
```
<sorted integers separated by space>
```
Testing OS Environment
-    Ubuntu 16.04, Ubuntu 14.04 

## Run command
```
gcc 0516222_4.c -o a.out -lpthread
./a.out
```
  
## Outout
![image](https://github.com/becca211137/operating_system/blob/master/lab4/result.png)
