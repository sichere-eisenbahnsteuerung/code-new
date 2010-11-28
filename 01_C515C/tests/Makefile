
include ../config.mk

SOURCE = \
	hardware_simulator.c \
	test_stub_util.c \
	test_helper.c \
	test_main.c \
	test_rs232.c \
	../drivers/rs232.c \
	../modules/betriebsmittelverwaltung/rs232_shared_memory.c \
	$(NULL)

all: build run

build:
	$(CC_HOST) $(SOURCE) -I../include -I../deps/check-0.9.8/build-host/src -I. -L../deps/check-0.9.8/build-host/src/.libs -lcheck -DTARGET_HOST -o test_main

run:
	LD_LIBRARY_PATH=../deps/check-0.9.8/build-host/src/.libs ./test_main

clean:
	rm test_main
