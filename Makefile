PWD := `pwd`
all: cppngrok.cpp
	@ g++ -c cppngrok.cpp -o ./build/cppngrok.o
	@ ar crv cppngrok_lib.a ./build/cppngrok.o --output build
	@ mv cppngrok_lib.a ./build
clean:
	@ shred -u ./build/cppngrok.o ./build/cppngrok_lib.a
