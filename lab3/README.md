# Lab3 - Parallel Merge Sort using Pthread

## Requirements
1. Prompt for the name of the input file
2. Read integers from the file
3. Do the sorting
4. Print the execution time of multi-thread sorting and single-thread sorting
    -    MT sorting should be much faster than ST sorting
    -    Their results must be exactly the same
5. Write the sorted array to a file
    -    output1.txt -> MT sorting
    -    output2.txt -> ST sorting

-    The cooperation among threads must be exactly the same as shown in the figure
-    Create all threads in the beginning of your program
-    Each of T1~T15 waits on its own semaphore
-    The main program signals the master thread T1 to start
-    T1 signals the 2nd-level threads T2 and T3 to start and so on
-    Use Bubble sort at the bottom level (T8~T15)
-    Single-thread sorting
        -    Use one single thread to do the same sorting, but no thread parallelism
        -    3 levels of array partitioning, bubble sort at the bottom level, and merge sub-arrays on return
        -    Should be noticeably slower than the multithreaded version

![](https://i.imgur.com/sejyvKk.png)

## Hints
**<pthread.h>**
-    Thread management : pthread_create, pthread_exit
-    Do not use pthread_join, use semaphore instead.

**<semaphore.h>**
-    Semaphore operations : sem_init, sem_wait, sem_post, sem_getvalue, sem_destroy


## Test Cases
**Input:**
```
<total # of integers><space>\n
<all integers separated by space>
```
-    Largest input: 1,000,000 integers
-    Generate your own file for testing

**Output**
-   sorted integers separated by space

Testing OS Environment
-    Ubuntu 16.04, Ubuntu 14.04 

## Run command
```
gcc 0516222_3.c -o a.out -lpthread
./a.out
```
## result
![image](https://github.com/becca211137/operating_system/blob/master/lab3/result.png)
