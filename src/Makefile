all: libllyx.a

libllyx.a: \
	BaseView.o \
	ButtonView.o \
	Elements.o \
	FPSView.o \
	ImageView.o \
	ProgressView.o \
	RootView.o \
	TableView.o \
	TextView.o \
	View.o
	$(AR) cr $@ $+

INCLUDES = -I../include -I../../eventpp/include `pkg-config --cflags sfml-graphics`

%.o: %.cpp
	$(CXX) $(INCLUDES) -std=c++17 -o $@ -c $<

clean:
	rm -f *.o libllyx.a
