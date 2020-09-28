// closh.c - COSC 315, Winter 2020
// YOUR NAME HERE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    int status;

    while (TRUE) { // main shell input loop

        // begin parsing code - do not modify
        printf("closh> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
        readCmdTokens(cmd, cmdTokens);
        do {
            printf("  count> ");
            count = readChar() - '0';
        } while (count <= 0 || count > 9);

        printf("  [p]arallel or [s]equential> ");
        parallel = (readChar() == 'p') ? TRUE : FALSE;
        do {
            printf("  timeout> ");
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code

        ////////////////////////////////////////////////////////
        //                                                    //
        // TODO: use cmdTokens, count, parallel, and timeout  //
        // to implement the rest of closh                     //
        //                                                    //
        // /////////////////////////////////////////////////////

        // just executes the given command once - REPLACE THIS CODE WITH YOUR OWN
        int childID;
        if (parallel == 0) {
            for (int x = 0; x < count - 1; x++) {
                childID = fork();

                if (childID == 0) {
                    sleep(1);
                    printf("this is childID (pid:%d)\n", (int)getpid());
                    execvp(cmdTokens[0], cmdTokens);
                    exit(EXIT_SUCCESS);
                    sleep(1);

                }
                else {
                    for (int x = 0; x < 8; x++) {
                        int endID = waitpid(childID, &status, 0);
                        if (endID == childID) {
                            break;
                        }
                        else {
                            sleep(1);
                        }
                    }
                }
            }
            execvp(cmdTokens[0], cmdTokens);

        }
        else if (parallel == 1) {
            for (int x = 0; x < count * 0.5; x++) {
                childID = fork();
            }
            if (childID == 0) {
                printf("this is childID (pid:%d)\n", (int)getpid());
                sleep(1);
                execvp(cmdTokens[0], cmdTokens);
            }
            else {
                printf("this is parent (pid:%d)\n", (int)getpid());
                sleep(1);
                execvp(cmdTokens[0], cmdTokens);
            }

        }




        // replaces the current process with the given program
       // doesn't return unless the calling failed
        printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
        exit(1);
    }
}

