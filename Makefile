.PHONY: build run

CC      = gcc
CFLAGS  = -lraylib -lm
FILES   = src/main.c

target: 
	mkdir -p $@

build: target
	$(CC) $(CFLAGS) -o target/sand $(FILES)

run: build
	./target/sand