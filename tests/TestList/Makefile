all: TestList

clean:
	rm -f TestList

INCLUDES = -I../../include `pkg-config --cflags sfml-system`

LIBS = `pkg-config --libs sfml-graphics sfml-system sfml-window`

TestList: TestList.cpp
	$(CXX) $(INCLUDES) -std=c++17 -o $@ $< ../../src/libllyx.a $(LIBS)
