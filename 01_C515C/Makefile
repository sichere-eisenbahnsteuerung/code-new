
include config.mk

TOPDIR = $(shell pwd)

all: build-tests run-tests

build-tests:
	make -C tests build

run-tests:
	make -C tests run

docs:
	doxygen Doxyfile

clean:
	make -C tests clean
	rm -rf build

