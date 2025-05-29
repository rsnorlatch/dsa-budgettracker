CC = clang++
CCFLAG = -g -O1 -fsanitize=address

all: clean run

run: main.plist main.exe
	@./build/main.exe

main.exe: main.cpp | ./build
	$(CC) $(CCFLAG) main.cpp -o ./build/main.exe

main.plist: main.cpp | ./plist
	$(CC) $(CCFLAG) --analyze main.cpp -o ./plist/main.plist

build_stable: main.cpp | ./build
	$(CC) main.cpp -o ./build/main.exe

./build:
	@mkdir ./build

./plist:
	@mkdir ./plist

clean:
	rm -rf ./build ./plist

clean-store:
	rm -rf ./store
