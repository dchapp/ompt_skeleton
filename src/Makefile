CXX=clang++
CFLAGS= -g -pedantic -std=c++14 -fopenmp -fPIC  #-Wall # -Werror 
INCLUDE= -I/. -I/ompt -I/g/g17/chapp1/repos/LLVM-openmp/build/include 

LDFLAGS= -L/. 
LD_LIBRARY_FLAGS= -L/. 
LIBS= 

all: skeletontool 
	
skeletontool: 
	$(CXX) $(CFLAGS) $(INCLUDE) -c tool.cpp -o tool.o
	$(CXX) -shared -o libskeletontool.so tool.o $(LDFLAGS) $(LD_LIBRARY_FLAGS) $(LIBS)
	cp libskeletontool.so ../lib/libskeletontool.so 


clean:
	rm -f *.o
	rm -f *.so 
	rm -f *.a 


