all: TestList

clean:
	rm -f TestList

INCLUDES = -I../../include `pkg-config --cflags sfml-graphics`

LIBS = `pkg-config --libs sfml-graphics`

TestList: TestList.cpp
	$(CXX) $(INCLUDES) -std=c++17 -o $@ $< ../../src/libllyx.a $(LIBS)
