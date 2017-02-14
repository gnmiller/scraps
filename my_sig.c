#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// headers
void catch_tstp(int);

// global flag
int global;

int main()
{

    if(signal(SIGTSTP,catch_tstp) == SIG_ERR)
    {
        fprintf(stderr,"failed to install sig handler...\n");
        exit(1);
    }

    global = 0;
    int i;
    i = 0;
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

void catch_tstp(int sig)
{
    if(sig==SIGTSTP)
    {
        if(global) global=0;
        else global=1;
    }
}
