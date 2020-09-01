#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_QTY (1024UL)

// Takes one argument, a count of random semantic versions to return

typedef struct {
    unsigned major;
    unsigned minor;
    unsigned patch;
    char     other[16];
} version_t;

static void
usage( const char *s )
{
    fprintf( stderr, "Usage:  %s <number of versions>\n", s );
}


int main( int argc, char *argv[] )
{
    unsigned long qty;

    if ( argc != 2 ) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }
    else {
        char *ep=NULL;
        errno=0;
        qty = strtoul( argv[1], &ep, 10 );
        if ( qty < 2  || qty > MAX_QTY  || errno != 0 || *ep ) {
            if ( ep && *ep )
                fprintf( stderr, "Invalid argument:  %s (I don't understand the part starting with \"%s...\")\n", argv[1], ep );
            if ( qty < 2 || qty > MAX_QTY )
                fprintf( stderr, "Invalid argument:  %s (Must be between 2-%lu)\n", argv[1], MAX_QTY  );
            if ( errno != 0 )
                fprintf( stderr, "Invalid argument: %s [%s]\n", argv[1], strerror(errno));

            usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    printf( "You want %lu random versions.\n", qty );

    return EXIT_SUCCESS;
}



