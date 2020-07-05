#
# Makefile for sampling and count
#

EXES1=hashtest.exe hashtest2.exe hashtestsampling.exe
EXES2=onesparsetest.exe onesparsetest2.exe
EXES3=s_sparsetest.exe
EXES=$(EXES1) $(EXES2) $(EXES3)
DEPS=../l0sampler.c ../count.c
CFLAGS=-std=c99 -Wall

all: $(EXES)

$(EXES): %.exe : %.c $(DEPS)
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean all

clean:
	rm -f $(EXES)
