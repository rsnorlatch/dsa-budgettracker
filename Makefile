CC = clang++
CCFLAGS = -fsanitize=address -g -O1 
LDFAGS = -fsanitize=address

all: clean main.plist main.exe run

main.exe: main.cpp | ./build
	${CC} ${CCFLAGS} main.cpp -o ./build/main.exe ${LDFLAGS}

main.plist: main.cpp | ./plist
	${CC} ${CCFLAGS} --analyze main.cpp -o ./plist/main.plist

./plist:
	@mkdir ./plist

./build:
	@mkdir ./build

clean:
	@rm -rf ./plist
	@rm -rf ./build

run:
	@./build/main.exe
