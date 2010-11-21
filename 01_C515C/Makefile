
include config.mk

TOPDIR = $(shell pwd)

all: build-tests run-tests

deps/check-0.9.8/build-host:
	mkdir -p $@

deps/check-0.9.8:
	tar xzf deps/check-0.9.8.tar.gz -C deps

deps/check-0.9.8/Makefile: deps/check-0.9.8 deps/check-0.9.8/build-host
	( cd deps/check-0.9.8/build-host ; ../configure )

deps/check-0.9.8/build-host/src/.libs/libcheck.la: deps/check-0.9.8/Makefile
	( cd deps/check-0.9.8/build-host ; make )

libcheck-host: deps/check-0.9.8/build-host/src/.libs/libcheck.la

build-tests: libcheck-host
	make -C tests build

run-tests:
	make -C tests run

clean:
	rm -rf build

