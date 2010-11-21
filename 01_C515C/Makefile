
include config.mk

TOPDIR = $(shell pwd)

SOURCE = \
	common/util.c \
	common/main.c \
	common/ringbuffer.c \
	$(NULL)

OBJFILES = $(patsubst %.c, %.obj, $(SOURCE))
OBJS = $(addprefix $(OBJDIR)/, $(OBJFILES))
HFILES = $(shell echo include/*.h)

all: build-firmware build-tests run-test run-ca

$(OBJS): $(HFILES)

$(OBJDIR)/%.obj: 
	$(CC) $< $(CFLAGS)

build-firmware: $(OBJ)

run-ca:
	@echo "Running coda analysis..."
	for f in $(SOURCE) ; do \
	  $(SPLINT) $(SPLINTFLAGS) $$f ; \
	done

deps/check-0.9.8/build-host:
	mkdir -p $@

deps/check-0.9.8:
	tar xzf deps/check-0.9.8.tar.gz -C deps

deps/check-0.9.8/Makefile: deps/check-0.9.8 deps/check-0.9.8/build-host
	( cd deps/check-0.9.8/build-host ; ../configure )

deps/check-0.9.8/build-host/src/.libs/libcheck.la: deps/check-0.9.8/Makefile
	( cd deps/check-0.9.8/build-host ; make )

build-tests: deps/check-0.9.8/build-host/src/.libs/libcheck.la

run-tests:

clean:
	rm -rf build

