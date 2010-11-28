
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

CHECK_LIBDIR = ../deps/check-0.9.8/build-host/src/.libs

TARGET_NAME = test_main
LIBS = -lcheck
INCS = -I../include -I../deps/check-0.9.8/build-host/src -I.
CFLAGS = $(INCS) -DTARGET_HOST
LDFLAGS = -o $(TARGET_NAME) $(LIBS) -L$(CHECK_LIBDIR)

OBJS = $(SOURCE:.c=.o)
OBJFILES = $(shell echo $(OBJS) | sed 's/\.\.\/drivers\///g' | sed 's/\.\.\/modules\/betriebsmittelverwaltung\///g')

all: build run

build: $(OBJS)
	gcc $(LDFLAGS) $(OBJFILES)

%.o: %.c 
	$(CC_HOST) -c $< $(CFLAGS)

run:
	LD_LIBRARY_PATH=$(CHECK_LIBDIR) ./$(TARGET_NAME)

clean:
	rm $(TARGET_NAME) $(OBJFILES)
