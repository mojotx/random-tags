#ifndef MAJ_VERSION_STRUCT_H
#define MAJ_VERSION_STRUCT_H

typedef struct {
    unsigned major;
    unsigned minor;
    unsigned patch;
    char     other[16];
} version_t;

void
print_ver( version_t t );

const char *
get_ver( version_t t );

bool
valid_ver( version_t t );

#endif /* MAJ_VERSION_STRUCT_H */
