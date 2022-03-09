all: TestProgress

clean:
	rm -f TestProgress

INCLUDES = -I../../include -I../../../eventpp/include `pkg-config --cflags sfml-graphics`

LIBS = `pkg-config --libs sfml-graphics`

TestProgress: TestProgress.cpp
	$(CXX) $(INCLUDES) -std=c++17 -o $@ $< ../../src/libllyx.a $(LIBS)
	