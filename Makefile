CC=x86_64-w64-mingw32-gcc
SRC=src/main
DEPS=src/headers
TARGETS=targets
SRS=$(SRC)/airfryer.c $(SRC)/fencrypt.c $(SRC)/fdecrypt.c $(SRC)/iterated.c

airfryer.exe: $(SRS) $(TARGETS)
	$(CC) -o $@ $(SRS) -I $(DEPS)
$(TARGETS):
	if ! [ -d $(TARGETS) ]; then 		\
		mkdir $(TARGETS);		\
	fi
	- cp * -r $(TARGETS)
clean:
	rm -rf *.exe
	rm -rf $(TARGETS)
