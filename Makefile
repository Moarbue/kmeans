CC=clang
CFLAGS=-Wall -Wextra -ggdb

AR=ar
AR_FLAGS=-rcs

OBJ=lib/point.o lib/kmeans.o

.PHONY: all mklibdir demo

all: mklibdir lib/libkmeans.a

lib/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

lib/libkmeans.a: $(OBJ)
	$(AR) $(AR_FLAGS) $@ $^

mklibdir:
	mkdir -p lib

demo/demo: demo/main.c lib/libkmeans.a
	$(CC) $(CFLAGS) -o $@ $< -Llib -lkmeans

demo: demo/demo

clean:
	rm -rf lib/ demo/demo*
