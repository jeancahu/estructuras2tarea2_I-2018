# Basic Makefile

CC = mpicc

TARGET = E1.x E2.x E3.x 

all: ${TARGET}

%.x: %.c
	${CC} $< -o $@

clean:
	rm -rf *.x

PHONY: all clean
