
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

OBJS = $(SOURCE:.c=.o)
OBJFILES = \
	$(patsubst '../drivers/%','',$(OBJS)) \
	$(patsubst '../modules/betriebsmittelverwaltung/%','',$(OBJS)) \
	$(NULL)

OBJFILES = `echo $(OBJS) | sed 's/\.\.\/drivers\///g' | sed 's/\.\.\/modules\/betriebsmittelverwaltung\///g'`

all: build run

build: $(OBJS)
	gcc -o test_main -lcheck -L../deps/check-0.9.8/build-host/src/.libs $(OBJFILES)

%.o: %.c 
	$(CC_HOST) -c $< -I../include -I../deps/check-0.9.8/build-host/src -I. -DTARGET_HOST

run:
	LD_LIBRARY_PATH=../deps/check-0.9.8/build-host/src/.libs ./test_main

clean:
	rm test_main
