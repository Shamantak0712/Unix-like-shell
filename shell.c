#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    char *line = NULL;
    size_t capacity = 0;
    char *argv[64];
    while(1){
        printf("echo>");
        if (getline(&line,&capacity,stdin)==-1){
            break;
        }
        char *token = strtok(line , " \t\n");
        int i =0;
        while (token != NULL){
            argv[i] = token;
            i++;
            token = strtok(NULL , " \t\n");
        }
        argv[i] = NULL;
        if(argv[0]==NULL){
            continue;
        }
        if(strcmp(argv[0],"cd")==0){
            if (argv[1]==NULL){
                printf("no such command");
                continue;
            }
            if ((chdir(argv[1]))==-1){
                perror("cd");
            }
            continue;
        }
        if (strcmp(argv[0],"exit")==0){
            exit(EXIT_SUCCESS);
            continue;
        }
        pid_t pid = fork();
        if(pid < 0){
            perror("fork");
        }
        else if(pid == 0){  
            execvp(argv[0],argv);
            perror("execvp"); 
            exit(EXIT_FAILURE);
        }
        else{
            waitpid(pid , NULL ,0);
            continue;
        }
    }
    return 0;
}
