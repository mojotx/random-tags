#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef __linux__
typedef unsigned char u_char;
# include <bsd/stdlib.h>
#endif
#include "random.h"
#include "colors.h"


bump_t
getBump(void)
{
    bump_t  b;

    // We will assume that 75% of the time, it's a patch
    // release, and 20% of the time it's a minor release,
    // and 5% it is a major release.
    uint32_t r = arc4random_uniform(100)+1;
    if ( r>=0 && r<= 75)
        b = PATCH;
    else if ( r > 75 && r <=95 )
        b = MINOR;
    else if ( r > 95 && r < 101 )
        b = MAJOR;
    else {
        fprintf( stderr, RED "ERROR in getBump(): unexpected value for r! Expected 1-100, got %u\n" NORMAL, r );
        exit(-1);
    }
    return b;
}


bool
bump( uint32_t qty )
{
    uint32_t limit = qty / 10;
    if (limit == 0)
        limit=1;
    return ( arc4random_uniform( qty ) <= limit ? true : false );
}

bool
yesorno( void )
{
    return (arc4random_uniform(2));
}
