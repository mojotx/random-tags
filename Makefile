CFLAGS=-O2 -Wall -Wextra -fstack-protector -fstack-protector-all -pipe -DNDEBUG
#CFLAGS=-g -Wall -Wextra -fstack-protector -fstack-protector-all -pipe
RM=rm -vfr
C_FILES=main.c version_struct.c random.c arg_parse.c
O_FILES=$(C_FILES:.c=.o)

OS=$(shell uname -s )

ifeq ($(OS), Linux)
CFLAGS+=-mtune=native
LIBS+=-lbsd
endif

ifeq ($(OS), Darwin)
CFLAGS+=-arch x86_64 -mmacosx-version-min=11.0
endif

.PHONY: rv clean test

all: rv

rv: $(O_FILES)
	$(CC) $(CFLAGS) -o $@ $(O_FILES)

clean:
	$(RM) rv $(O_FILES) output.tmp

test: rv
	./run-test.sh
