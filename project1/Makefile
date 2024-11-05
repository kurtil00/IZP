
.PHONY: run clean

run: tnine
	@./tnine $(ARGS) <seznam.txt

tnine: tnine.c
	@gcc tnine.c -Wall -std=c11 -o tnine
	
clean:
	rm -f tnine.exe