CXX = g++
CXXFLAGS = -Wall -Wextra

build/main: build/main.o
	mkdir -p build
	$(CXX) -o build/main build/main.o

build/main.o: src/main.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c -o build/main.o src/main.cpp

clean:
	rm -rf build
