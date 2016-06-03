all:
	clear && mkdir -p build && cd build && cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ .. && make
clean:
	rm -rf ./build/
