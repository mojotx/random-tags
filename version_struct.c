#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "version_struct.h"

void
print_ver( version_t t )
{
    if ( strlen( t.other ) > 0 )
        printf( "v%u.%u.%u-%s\n", t.major, t.minor, t.patch, t.other );
    else
        printf( "v%u.%u.%u\n", t.major, t.minor, t.patch );
}

const char *
get_ver( version_t t )
{
    static char version[32];

    memset(version, 0, sizeof(version));
    if ( strlen( t.other ) > 0 )
        snprintf( version, sizeof(version)-1, "v%u.%u.%u-%s", t.major, t.minor, t.patch, t.other );
    else
        snprintf( version, sizeof(version)-1, "v%u.%u.%u", t.major, t.minor, t.patch );

    return version;
}

bool
valid_ver( version_t t )
{
    return ( t.major > 0 || t.minor > 0 || t.patch > 0 );
}
