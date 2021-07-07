LIB_OUT = libcapture.so

all: bin

bin:
	make -C build

test: bin
	rm -f build.db
	build/init_session build.db
	LD_PRELOAD=`realpath build/libcapture.so` gcc -o sample sample.c
	build/fini_session build.db

claen:
	make -C build clean
