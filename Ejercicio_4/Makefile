# Basic Makefile

INPUT_00 = prom_scatter_plus_gather.c
INPUT_01 = prom_scatter_plus_reduce.c

TARGET_00 = prom_scatter_plus_gather.x
TARGET_01 = prom_scatter_plus_reduce.x

all: ${TARGET_00} ${TARGET_01}

${TARGET_00}: ${INPUT_00}
	mpicc -o ${TARGET_00} ${INPUT_00}

${TARGET_01}: ${INPUT_01}
	mpicc -o ${TARGET_01} ${INPUT_01}

# %.c:

clean:
	rm -rf *.x

PHONY: all clean
