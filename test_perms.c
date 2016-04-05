#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void SIGUSR1handler( int );
int flag = 0;

/**
 * Test how a system handles open fds if the permissions of the open file are adjusted.
 * Attempts to open argv[1] if specified or ./test.txt
 */
int main(int argc, char** argv){

        // setting up....
        char *f_name,*writeout;
        f_name = (char*)malloc( sizeof( char ) * 80 );
        writeout = (char*)malloc( sizeof( char ) * 80 );
        strcpy( writeout, "This is a test string!\n" );

        //install signal handler on SIGUSR1...
        signal(SIGUSR1, SIGUSR1handler );

        if ( f_name <= 0 )
        {
                fprintf( stderr, "malloc failed\n" );
                free( f_name );
                free( writeout );
                exit( 1 );
        }

        if ( argc <= 1 )
        {
                fprintf( stderr, "No file specified, assuming ./temp.txt\n" );
                strcpy( f_name, "./test.txt" );
        }
        else
        {
                if( strlen( argv[1] ) >= 79 ){
                        fprintf( stderr, "File name too long (>80)!\n" );
                        free( f_name );
                        free( writeout );
                        exit( 1 );
                }
                strcpy( f_name, argv[1] );
                fprintf( stdout, "Using %s as the file name.\n", f_name );
        }


        // actually start doing stuff...
        fprintf( stdout, "Attempting to open %s in RW mode...\n", f_name );
        int fd;
        fd = 0;
        fd = open ( f_name, O_RDWR );
        if ( fd == 0 )
        {
                fprintf( stderr, "Failed to open %s in RW mode.\n", f_name ) ;
                close( fd );
                free( f_name );
                free( writeout );
                exit( 1 );
        }
        else{
                fprintf( stdout, "%s opened in RW mode.\n", f_name );
                fprintf( stdout, "Now awaiting SIGUSR1 input to proceed..." );
                while( flag == 0 )
                {
                        sleep( 10 );
                        fprintf( stdout, "....\nStill waiting for SIGUSR1\n");
                }
                fprintf( stdout, "SIGUSR1 caught!\nAttempting to write %s into %s now...\n", writeout, f_name );
                if ( write( fd, writeout, 80 ) <= 0 )
                {
                        fprintf( stderr, "Failed to write to %s!\n", f_name );
                        close( fd );
                        free( f_name );
                        free( writeout );
                        exit ( 1 );
                }
                else
                {
                        fprintf( stdout, "Successfully wrote to %s!\nCleaning up and terminating now\n", f_name );
                        close( fd );
                        free( f_name );
                        free( writeout );
                        exit( 0 );
                }
        }

        exit( 0 );
}

void SIGUSR1handler( int sig )
{
        flag = 1;
        return;
}
