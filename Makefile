# Basic Makefile

INPUT_00 = com2p.c

TARGET_00 = com2p.x

all: ${TARGET_00}

${TARGET_00}: ${INPUT_00}
	mpicc -o ${TARGET_00} ${INPUT_00}

# %.c:

clean:
	rm -rf *.x

PHONY: all clean
