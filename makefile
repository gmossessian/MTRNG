CC = clang

CFILES = MTRNG.c


compile: $(CFILES)
	$(CC) -c $(CFILES)
	ar -cvq libMTRNG.a MTRNG.o
