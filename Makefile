PWD := `pwd`
all: cppngrok.cpp
	@ mkdir -p build
	@ g++ -c cppngrok.cpp -o ./build/cppngrok.o
	@ ar crv cppngrok_lib.a ./build/cppngrok.o --output build
	@ mv cppngrok_lib.a ./build
shared:
	@ g++ -c -fpic -o ./build/cppngrok_so.o cppngrok.cpp
	@ g++ -shared -o ./build/cppngrok_slib.so ./build/cppngrok_so.o
clean:
	@ shred -u ./build/cppngrok.o ./build/cppngrok_lib.a
