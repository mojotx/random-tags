#ifndef MAJ_RANDOM_H
#define MAJ_RANDOM_H

#include <stdbool.h>

typedef enum bump { MAJOR, MINOR, PATCH } bump_t;

bump_t getBump(void);

#endif /* MAJ_RANDOM_H */
