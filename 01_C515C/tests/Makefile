
include ../config.mk

SOURCE = \
	hardware_simulator.c \
	test_stub_util.c \
	test_main.c \
	test_rs232.c \
	test_xpressnet.c \
	ctest/ctest.c \
	../drivers/rs232.c \
	../drivers/xpressnet.c \
	../modules/betriebsmittelverwaltung.c \
	$(NULL)

CHECK_LIBDIR = ../deps/check-0.9.8/build-host/src/.libs

TARGET_NAME = test_main
LIBS = 
INCS = -I../include -I. -Ictest
CFLAGS = $(INCS) -DTARGET_HOST -g
LDFLAGS = -o $(TARGET_NAME) $(LIBS) -L$(CHECK_LIBDIR)

OBJS = $(SOURCE:.c=.o)
OBJFILES = $(shell echo $(OBJS) | sed 's/\.\.\/drivers\///g' | sed 's/\.\.\/modules\///g' | sed 's/ctest\///g')

TEST_DATE = $(shell echo `date +%Y%m%d%H%M`)

all: build run

build: $(OBJS)
	gcc $(LDFLAGS) $(OBJFILES)

%.o: %.c 
	$(CC_HOST) -c $< $(CFLAGS)

logs:
	mkdir -p logs

run: logs
	LD_LIBRARY_PATH=$(CHECK_LIBDIR) ./$(TARGET_NAME) --test-date='$(TEST_DATE)'
#	xsltproc common/style.xsl logs/$(TEST_DATE)_results.xml > $(TEST_DATE)_results.html

clean:
	rm $(TARGET_NAME) $(OBJFILES)

