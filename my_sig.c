#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// headers
void catch();

// global flags
int global;
int allow;

int main()
{
    // set up globals
    allow = 0;
    global = 0;

    // install signal handlers
    if(signal(SIGTSTP,catch) == SIG_ERR || signal(SIGUSR1,catch) == SIG_ERR)
    {
        fprintf(stderr,"failed to install sig handler...\n");
        exit(1);
    }

    // useless loop
    for(;;)
    {
        if(global){
            fprintf(stdout,"global set...\n");
        } else {
            fprintf(stdout,"global unset...\n");
        }
        sleep(1);
    }
}

/** catch SIGTSTP and SIGUSR1 
 * SIGTSTP alters global flag to change output
 * SIGUSR1 allows or denys the use of SIGTSTP
 */
void catch(int sig)
{
    if(sig==SIGTSTP)
    {
        if(allow){
            if(global) global=0;
            else global=1;
        }
    }
    if(sig==SIGUSR1){
        allow=!allow;
    }
}

