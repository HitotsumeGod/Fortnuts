CC=x86_64-w64-mingw32-gcc
SRC=src/main
DEPS=src/headers
SRS=$(SRC)/fortnuts.c

fortnuts.exe: $(SRS)
	$(CC) -o $@ $^ -I $(DEPS)
clean:
	rm -rf *.exe
