# Lab1 - A Simple Shell
Design a simple shell can take command like "clear" "ls" ...

## Functions
### 1. Control flow of your simple shell:
- Display the prompt sign “>” and take a string from user
- Parse the string into a program name and arguments
- Fork a child process
- Have the child process execute the program
- Wait until the child terminates
- Go to the first step
### 2. Waiting on child processes
-    If a command is ended with “&”, then the shell will not be blocked on a child process
-    For example:
        -    sleep 10s
            -    The prompt re-appears after 10 seconds
        -    sleep 10s &
            -    The prompt re-appears immediately
-    A child process becomes a zombie if it is not waited by its parent process
    -    How to deal with this problem?

## Test Cases
Your shell must correctly handle test cases of the following format
-    Do not leave zombie processes in the system before or after your shell terminate
-    Do not use system() 
```
<program> <arg1> <arg2> <…>
```
Test cases are like the following, but not limited to:
```
clear
ls -l
cp a.txt b.txt
cat c.txt &
```
**Bonus**

I/O redirection (+10 pts)
```
ls –l > a.txt
```
Pipe (+10 pts)
```
ls | more
```
No multiple or combined redirections
```
a | b | c
a < b > c
a | b > c
```
Testing OS Environment
-    Ubuntu 16.04, Ubuntu 14.04 
## Hints
- fork()
    -   Create a child process
    -   http://man7.org/linux/man-pages/man2/fork.2.html
- exec() family
    -   Have the current process execute the program specified in the pathname
    -   http://man7.org/linux/man-pages/man3/exec.3.html
- wait() family
    -   wait() wait the termination of anyone of the child processes
    -   waitpid() waits the termination of the specified child process
    -   http://man7.org/linux/man-pages/man2/waitpid.2.html
## run command

```
g++ 0516222_hw1.c -o a.out
./a.out
```

## Output
![image](https://user-images.githubusercontent.com/22147510/147545125-7f35c911-9942-429a-ba9e-377288dcb92c.png)
