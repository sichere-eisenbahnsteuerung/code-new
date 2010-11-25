
include ../config.mk

SOURCE = \
	hardware_simulator.c \
	test_stub_util.c \
	test_helper.c \
	test_main.c \
	$(NULL)

all: build run

build:
	$(CC_HOST) $(SOURCE) -I../include -I../deps/check-0.9.8/build-host/src -L../deps/check-0.9.8/build-host/src/.libs -lcheck -o test_main

run:
	LD_LIBRARY_PATH=../deps/check-0.9.8/build-host/src/.libs ./test_main

clean:
	rm test_main
