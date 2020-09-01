#include <stdlib.h>
#include <stdbool.h>
#include "random.h"

bool
bump( void )
{
    return ( arc4random_uniform( 100 ) <= 25 ? true : false );
}

bool
yesorno( void )
{
    return (arc4random_uniform(2));
}
