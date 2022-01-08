# Lab2 - Multi-Process Matrix Multiplication using Shared Memory
Basic parallel processing : Matrix multiplication using multiple processes

## Requirements
-    Create worker processes using fork()
-    Wait until all worker processes have exit()’ed
-    Put all the metrics in the shared memory
-    Print the elapsed time and matrix checksum
        -    16 cases, process parallelism from 1 to 16
        -    The final checksum must be correct
-    Matrix elements and the checksum are 32-bit unsigned integers
-    2-process and 3-process versions must be noticeably faster than 1-process version
![](https://i.imgur.com/iVBeMCt.png)

## Hints
-    shmget() – create a block of shared memory
-    shmat() – attach shared memory to the current process’s address space 
-    shmdt() – detach shared memory from the current  process’s address space
-    shmctl() – control shared memory
-    gettimeofday()

## Test Cases
**Input:**
-    the dimension of two square matrices A & B(between 100-800)
-    E.g., 100 (A, B, and C are 100x100 square matrices)
![image](https://user-images.githubusercontent.com/22147510/148645713-9c629ee5-32bb-41a9-89fa-596f6a77bae3.png)

**Output**
-    an execution time and a checksum

Testing OS Environment
-    Ubuntu 16.04, Ubuntu 14.04 

## Run command

```
g++ 0516222_hw2.c -o a.out
./a.out
```
## running result
![image](https://github.com/becca211137/operating_system/blob/master/lab2/result1.png)
