CFLAGS=-O2 -Wall -Wextra -fstack-protector -fstack-protector-all -pipe -arch x86_64 -mmacosx-version-min=10.15
RM=rm -vfr

rv: versions.c
	$(CC) $(CFLAGS) -o $@ versions.c

clean:
	$(RM) rv
