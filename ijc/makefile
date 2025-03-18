cc = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

all: primes

primes:
	$(cc) $(CFLAGS) primes.c -o primes.exe
	$(cc) -DUSE_INLINE $(CFLAGS) primes.c -o primes-i.exe
	$(cc) -MM *.c > dep;

m32:
	$(cc) -m32 $(CFLAGS) eratosthenes.c -o eratosthenes.exe