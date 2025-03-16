WCC=x86_64-w64-mingw32-gcc
LIBS=libs/libcurl.dll.a
BUILD=build

fortnutsl: src/main/windows/fortnuts.c
	$(WCC) -o fortnuts.exe $^ -I /usr/lib/mingw64_curl/include -L /usr/lib/mingw64_curl/lib -lcurl
$(BUILD)/fortnuts.o: src/main/windows/fortnuts.c
	mkdir $(BUILD)
	$(WCC) -c -o $@ $^ -I /usr/lib/mingw64_curl/include
fortnuts.exe: $(BUILD)/fortnuts.o
	$(WCC) -static -o $@ $^ $(LIBS)
	rm -r $(BUILD)
