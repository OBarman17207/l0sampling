#
# Makefile for sampling and count
#

EXE1=count.exe
EXE2=sampling.exe
EXES=$(EXE1) $(EXE2)
DEPS=l0sampler.c
CFLAGS=-std=c99 -Wall

all: $(EXES)

$(EXES): %.exe : %.c $(DEPS)
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean all

clean:
	\rm -f $(EXES)
	\rm -f *.o
