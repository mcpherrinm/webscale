CC=LD_PRELOAD=/users/mimcpher/code/webc/libhttpfile.so gcc

libhttpfile.so: libhttpfile.c
	gcc -O2 -Wall -shared -ldl -fPIC libhttpfile.c -o libhttpfile.so -lcurl

test: test.c

data: data.c
