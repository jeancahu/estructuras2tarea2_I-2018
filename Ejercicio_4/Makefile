# Basic Makefile

INPUT_00 = prom_scatter_plus_gather.c

TARGET_00 = prom_scatter_plus_gather.x

all: ${TARGET_00}

${TARGET_00}: ${INPUT_00}
	mpicc -o ${TARGET_00} ${INPUT_00}

# %.c:

clean:
	rm -rf *.x

PHONY: all clean
