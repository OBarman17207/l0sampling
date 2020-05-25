#
# Makefile for sampling and count
#

EXES1=hashprove.exe hashprove2.exe hashprove3.exe hashprove4.exe hashprove5.exe
EXES2=onesparseprove.exe onesparseprove2.exe
EXES3=s_sparseprove.exe s_sparseprove2.exe
EXES4=s_sparse_hash2.exe
EXES=$(EXES1) $(EXES2) $(EXES3) $(EXES4)
DEPS=~/l0sampling/l0sampler.c
CFLAGS=-std=c99 -Wall

all: $(EXES)

$(EXES): %.exe : %.c $(DEPS)
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean all

clean:
	rm -f $(EXES)
