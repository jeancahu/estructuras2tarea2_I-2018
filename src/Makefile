# Basic Makefile

CC = mpicc

TARGET = E1.x E2.x E3.x EOpc1.x EOpc2.x EOpc3.x Prime_sec_algorithm.x prom_scatter_plus_gather.x prom_scatter_plus_reduce.x

all: ${TARGET}

%.x: %.c
	${CC} $< -o $@

clean:
	rm -rf *.x

PHONY: all clean
