#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "version_struct.h"
#include "random.h"
#include "arg_parse.h"

#define MAX_QTY (1024UL)

const bool debug = false;

// Takes one argument, a count of random semantic versions to return

int main( int argc, char *argv[] )
{

    if ( argc != 2 ) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }


    unsigned long   qty = parse_qty( argv[1] );

    if (debug)
        printf( "You want %lu random versions.\n", qty );

    // Start with v0.0.1
    version_t       v = { 0, 0, 1, "" };


    version_t       *data;
    if ((data = calloc( qty, sizeof(version_t))) == NULL ) {
        fprintf( stderr, "Cannot allocate enough memory for %lu versions!\n", qty );
        return EXIT_FAILURE;
    }

    for (unsigned long i=0; i<qty; ++i) {

        if (debug) {
            printf( "%lu: ", i+1 );
            print_ver( v );
        }

        data[i] = v;

        if ( bump() ) {
            if (debug)
                printf ("BuMp!" );

            if ( yesorno() ) {
                if (debug)
                    printf ("(major) %s to ", get_ver(v) );
                v.major++;
                v.minor=0;
                v.patch=0;
                if (debug)
                    printf( " %s\n", get_ver(v) );
            }
            else {
                if (debug)
                    printf( "(minor) %s to ", get_ver(v) );
                v.minor++;
                v.patch=0;
                if (debug)
                    printf( " %s\n", get_ver(v));
            }
        }
        else {
            v.patch++;
        }

    }

    if (debug)
        printf( "\e[36m" );
    // Now print them in random order
    unsigned long rem=qty;
    while ( rem > 0 ) {
        unsigned long i = arc4random_uniform( rem + 1 );
        if(debug)
            printf( "%lu: ", rem );
        print_ver( data[i] );

        // Shift
        for ( ; i<rem; ++i ) {
            if ( i+1 < rem ) {
                data[i]=data[i+1];
            }
        }

        rem--;
    }
    if (debug)
        printf( "\e[0m" );


    return EXIT_SUCCESS;
}
