all: TestSimple

clean:
	rm -f TestSimple

INCLUDES = -I../../include -I../../../eventpp/include `pkg-config --cflags sfml-system`

LIBS = `pkg-config --libs sfml-graphics sfml-system sfml-window`

TestSimple: TestSimple.cpp
	$(CXX) $(INCLUDES) -std=c++17 -o $@ $< ../../src/libllyx.a $(LIBS)
