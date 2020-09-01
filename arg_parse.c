#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "random.h"

void
usage( const char *s )
{
    fprintf( stderr, "Usage:  %s <number of versions>\n", s );
}

unsigned long
parse_qty( const char *s )
{
    if ( s == NULL || strlen(s) == 0 ) {
        fprintf( stderr, "Fatal error in parse_qty, NULL pointer or empty string.\n" );
        exit( EXIT_FAILURE );
    }

    errno=0;
    char *ep=NULL;

    unsigned long qty = strtoul( s, &ep, 10 );

    if ( qty == 0 || errno != 0 || *ep ) {
        if ( ep && *ep )
            fprintf( stderr, "Invalid argument:  %s (I don't understand the part starting with \"%s...\")\n", s, ep );
        if ( qty == 0 )
            fprintf( stderr, "Invalid argument:  %s (Must be non-zero)\n", s );
        if ( errno != 0 )
            fprintf( stderr, "Invalid argument: %s [%s]\n", s, strerror(errno));

        exit( EXIT_FAILURE );
    }

    return qty;

}

