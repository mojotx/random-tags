#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <getopt.h>
#include <ctype.h>
#include "version_struct.h"
#include "random.h"
#include "arg_parse.h"
#include "colors.h"

bool debug = false;
bool randomize = false;

// Takes one argument, a count of random semantic versions to return

int main( int argc, char *argv[] )
{

    if ( argc < 2 ) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    opterr=0;
    int c;
    while ((c = getopt( argc, argv, "hdr")) != -1) {
        switch(c) {
            case 'd':
                debug = true;
                break;

            case 'h':
                fputs( BRIGHT BLACK "You asked for help\n" NORMAL, stderr );
                usage(argv[0]);
                return EXIT_FAILURE;

            case 'r':
                randomize = true;
                break;

            case '?':
            default:
                if (isprint(optopt))
                    fprintf( stderr, RED "Error: Unknown option '-%c'\n" NORMAL, optopt );
                else
                    fprintf( stderr, RED "Error: Unknown option '\\x%x'\n" NORMAL, optopt );
                return EXIT_FAILURE;
                break;

        }
    }

    if (debug) {
        fputs( BRIGHT BLACK "DEBUG: On\n" NORMAL, stderr );
        if ( randomize )
            fputs( BRIGHT BLACK "Randomize: On\n" NORMAL, stderr );
    }

    unsigned long   qty;
    if (optind < argc)
       qty  = parse_qty( argv[optind] );
    else {
        usage( argv[0] );
        return EXIT_FAILURE;
    }

    if (debug)
        fprintf( stderr, BRIGHT BLACK "You want %lu random versions.\n" NORMAL, qty );

    // Start with v0.0.1
    version_t       v = { 0, 0, 1, "" };

    version_t       *data;
    if ((data = calloc( qty, sizeof(version_t))) == NULL ) {
        fprintf( stderr, "Cannot allocate enough memory for %lu versions!\n", qty );
        return EXIT_FAILURE;
    }

    for (unsigned long i=0; i<qty; ++i) {

        if (debug) {
            fprintf( stderr, BRIGHT BLACK "%lu: %s\n" NORMAL, i+1, get_ver(v) );
        }

        data[i] = v;

        bump_t b = getBump();
        switch (b) {
            case MAJOR:
                if (debug) {
                    fprintf( stderr, BRIGHT BLACK "BUMP (major) %s to " NORMAL, get_ver(v) );
                }
                v.major++;
                v.minor=0;
                v.patch=0;
                if (debug)
                    fprintf( stderr, BRIGHT BLACK " %s\n" NORMAL, get_ver(v) );
                break;

            case MINOR:
                if (debug)
                    fprintf( stderr, BRIGHT BLACK  " BUMP (minor) %s to " NORMAL, get_ver(v) );
                v.minor++;
                v.patch=0;
                if (debug)
                    fprintf( stderr, BRIGHT BLACK " %s\n" NORMAL, get_ver(v));
                break;
            case PATCH:
                v.patch++;
                break;
            default:
                fprintf( stderr, RED "UNKNOWN bump value %d!\n" NORMAL, (int)(b) );
                break;
        }

    }

    if ( randomize ) {
        unsigned long rem=qty;
        while ( rem > 0 ) {
            unsigned long i = arc4random_uniform( rem + 1 );
            if(debug)
                fprintf( stderr, BRIGHT BLACK "%lu: " NORMAL, rem );
            print_ver( data[i] );

            // Shift
            for ( ; i<rem; ++i ) {
                if ( i+1 < rem ) {
                    data[i]=data[i+1];
                    assert( valid_ver( data[i] ) );
                }
            }

            rem--;
        }
    }
    else
        for (unsigned long i=0; i<qty; i++)
            print_ver( data[i] );

    return EXIT_SUCCESS;
}
