/*standard c libraries and unix system headers to build a unix or linux shell*/
#include <stdio.h> // basic input output
#include <stdlib.h> // utility library for memory allocation and handling
#include <string.h> // lib for string handling
#include <unistd.h> //used to create child processes and system level calls
#include <sys/types.h> //define system data types 
#include <sys/wait.h> //process waiting and termination

#define MAX_INPUT 1024 //maximum length of command line input
#define MAX_ARGS 64 //max number of arguments
#define HISTORY_SIZE 10

char history[HISTORY_SIZE][MAX_INPUT];
int history_count = 0;

//converts RAW command string into array of argument pointers
void parse_input(char *input, char **args) {
    int i=0;

 // strtok splits inputs into tokens that use space and newlines as delimiters   
    char *token = strtok(input, " \n");
    while(token != NULL && i < MAX_ARGS-1){
        args[i++]= token;
        token = strtok(NULL, " \n");
    }
    args[i]=NULL;
}

int main(){
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

// shell main loop
    while(1){
        printf("mini-shell> ");
        fflush(stdout); //display shell prompt and flush

        if(fgets(input, sizeof(input), stdin)==NULL){
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;

//store here
        if (strlen(input)>0){
            strncpy(history[history_count % HISTORY_SIZE], input, MAX_INPUT);
            history_count++;
        }

        parse_input(input, args);

        if(args[0]==NULL)
            continue;
        if(strcmp(args[0], "exit")==0){
            printf("Exiting shell...\n");
            break;
        }
        //built-in cd command
        if (strcmp(args[0], "cd")==0){
            if(args[1]==NULL){
                fprintf(stderr,"cd: missing argument\n");
            }
            else{
                if (chdir(args[1])!=0){
                    perror("cd failed");
                }
            }
            continue;
        }

        // Built-in history
        if (strcmp(args[0], "history") == 0) {
            int start = history_count > HISTORY_SIZE ? history_count - HISTORY_SIZE : 0;
            for (int i = start; i < history_count; i++) {
                printf("%d %s\n", i + 1, history[i % HISTORY_SIZE]);
            }
            continue;
        }

        int background = 0;
        int i=0;

        while (args[i] != NULL){
            i++;
        }

        if (i> 0 && strcmp(args[i-1], "&")==0){
            background =1;
            args[i-1]=NULL;
        }

        
// create child process
        pid_t pid= fork();

        if(pid<0){
            perror("Fork failed");
        }
        else if(pid==0){
            if(execvp(args[0],args)<0){
                perror("Execution failed");
            }
            exit(1);
        }
        else{

            // parent process
            // wait for child process to finish
            if (!background){
                wait(NULL);
            }
            else{
                printf("Started background process with PID: %d\n", pid);
            }
        }
    }
    return 0;
}