CFLAGS=-O2 -Wall -Wextra -fstack-protector -fstack-protector-all -pipe -arch x86_64 -mmacosx-version-min=10.15
RM=rm -vfr
C_FILES=versions.c version_struct.c random.c arg_parse.c
O_FILES=$(C_FILES:.c=.o)

rv: $(O_FILES)
	$(CC) $(CFLAGS) -o $@ $(O_FILES)

clean:
	$(RM) rv $(O_FILES)
