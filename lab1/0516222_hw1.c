#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#define file_leng 2000
#define basic 0
#define special 1
#define redirection 2
#define pip 3


void run(int status, char *input){
    char *file_name,*temp,*argv_0[file_leng], *argv_1[file_leng];
    int stdout_copy_fd,file_fd, argc_0 = 0, argc_1 = 0;
    pid_t pid, pid_for_specail, pid_for_pipe;
    pid = fork();

    if (pid < 0) 
    {
      printf("Fork Failed\n");
      exit(-1);
    }
    else if (pid == 0){
        char *temp = strtok(input, "\n");
        switch(status){
            case basic:
                temp = strtok(temp, " ");
                for( ;temp != NULL; argv_0[argc_0] = temp, temp = strtok(NULL," "), argc_0++);
                argv_0[argc_0] = NULL;
                execvp(argv_0[0], argv_0);
            case special:
                pid_for_specail = fork();
                if(pid_for_specail < 0){
                    printf("Fork Failed\n");
                    exit(-1);
                }
                else if(pid_for_specail == 0){    
                    temp = strtok(temp, "&");            
                    temp = strtok(temp, " ");
                
                    for( ;temp != NULL; argv_0[argc_0] = temp, temp = strtok(NULL," "), argc_0++);
                    argv_0[argc_0] = NULL;
                    argv_0[argc_0+1] = NULL;
                    execvp(argv_0[0], argv_0);
                }
                else{
                    exit(0);
                }
            case redirection:
                file_name = strtok(strstr(temp, ">")+1, " ");
                temp = strtok(temp, ">");
                temp = strtok(temp, " ");
                for( ;temp != NULL; argv_0[argc_0] = temp, temp = strtok(NULL," "), argc_0++);
               
                file_fd=open(file_name,O_WRONLY | O_CREAT,0644);
                dup2(file_fd,STDOUT_FILENO );
                close(file_fd);
                execvp(argv_0[0], argv_0);
            case pip:
                char  *behind, *str, *front;
                
                behind = strstr(temp, "|")+1;
                temp = strtok(temp, "|");
                str = strtok(behind, " ");
                for(;str != NULL; argv_1[argc_1++] = str, str = strtok(NULL, " ")); 
                argv_1[argc_1] = NULL;
                front = strtok(temp, " ");
                for(;front != NULL;argv_0[argc_0++] = front, front = strtok(NULL, " "));
                argv_0[argc_0] = NULL;

                int pipefd[2];
                pipe(pipefd);
                pid_for_pipe = fork();
                if(pid_for_pipe < 0) {
                    printf("Fork Failed\n");
                    exit(-1);
                }
                else if(pid_for_pipe == 0) {
                    close(pipefd[0]);
                    dup2(pipefd[1], 1);
                    close(pipefd[1]);
                    execvp(argv_0[0], argv_0);		
                }
                else {
                    wait(NULL);
                    close(pipefd[1]);
                    dup2(pipefd[0], 0);
                    close(pipefd[0]);
                    execvp(argv_1[0], argv_1);
                }
        }
    }
    else{
        wait(NULL);
    }

}

int main(){
    while(1){
        printf(">");
        char input[file_leng];
        fgets(input, file_leng, stdin);
        int status= basic ;
        if( strchr(input, '&') != NULL)
            status = special;
        else if(strchr(input, '|') != NULL)
            status = pip;
        else if(strchr(input, '>') != NULL || strchr(input, '<') != NULL )
            status = redirection;
        else
            status = basic;
        run(status, input);
    }
    return 0;
}