WCC=x86_64-w64-mingw32-gcc
LIBS=libs/libcurl.dll.a
DEPS=src/headers
BUILD=build

fortnuts.exe: $(BUILD)/fortnuts.o
	$(WCC) -static -o $@ $^ $(LIBS) -g
	rm -rf $(BUILD)
fortnuts-dynamic.exe: src/main/windows/fortnuts.c
	$(WCC) -o $@ $^ -I $(DEPS) -L libs -lcurl
$(BUILD)/fortnuts.o: src/main/windows/fortnuts.c
	mkdir $(BUILD)
	$(WCC) -c -o $@ $^ -I $(DEPS)
clean:
	rm -f *.exe
	rm -f *.txt
	ls
