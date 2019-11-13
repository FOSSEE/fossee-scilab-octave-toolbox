LIBNAME = fun

all: lib$(LIBNAME).so test$(LIBNAME)

$(LIBNAME).o: $(LIBNAME).h $(LIBNAME).cpp
	mkoctfile -c -fPIC $(LIBNAME).cpp

lib$(LIBNAME).so: $(LIBNAME).o
	g++ -loctave -loctinterp -shared -o lib$(LIBNAME).so $(LIBNAME).o

test$(LIBNAME): lib$(LIBNAME).so main.cpp fun.h
	g++ -Wall -L$(PWD) -Wl,-rpath=$(PWD) -o $@ main.cpp -l$(LIBNAME) -g -loctave -loctinterp

install:
	cp fun.h ../thirdparty/linux/include/
	cp libfun.so ../thirdparty/linux/lib/x64/

.PHONY: clean
clean:
	$(RM) -f *.out *.so *.o *.oct
