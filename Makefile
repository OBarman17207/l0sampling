#
# Makefile for sampling and count
#

EXE1=l0sampling.exe
EXE2=reservoir_sampling.exe
EXES=$(EXE1) $(EXE2)
DEPS=l0sampler.c count.c
CFLAGS=-std=c99 -Wall

all: $(EXES)

$(EXES): %.exe : %.c $(DEPS)
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean all

clean:
	rm -f $(EXES)
