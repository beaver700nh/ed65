.PHONY: all clean build run

all: build run

clean:
	rm -r build

build:
	(cd build; cmake ..; make -j4)

run:
	./build/bin/ed65

