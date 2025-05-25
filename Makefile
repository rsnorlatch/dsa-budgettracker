CC = clang++

all: clean main.plist main.exe run

main.exe: main.cpp | ./build
	@echo "compiling main.cpp..."
	@${CC} main.cpp -o ./build/main.exe

main.plist: main.cpp | ./plist
	@echo "analyzing main.cpp..."
	@${CC} --analyze main.cpp -o ./plist/main.plist

./plist:
	@mkdir ./plist

./build:
	@mkdir ./build

clean:
	@rm -rf ./plist
	@rm -rf ./build

run:
	@./build/main.exe
