all: TestSimple

clean:
	rm -f TestSimple

INCLUDES = -I../../include -I../../../eventpp/include `pkg-config --cflags sfml-graphics`

LIBS = `pkg-config --libs sfml-graphics`

TestSimple: TestSimple.cpp
	$(CXX) $(INCLUDES) -std=c++17 -o $@ $< ../../src/libllyx.a $(LIBS)
