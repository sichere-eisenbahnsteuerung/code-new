
include ../../config.mk

SOURCE = \
    ../ctest/ctest.c \
	../hardware_simulator.c \
	rs232_main.c \
    ../test_stub_util.c \
	rs232_stub.c \
	rs232_win_linux.c \
	../../drivers/xpressnet.c \
	../../modules/betriebsmittelverwaltung.c \
	$(NULL)

TARGET_NAME = rs232_main
LIBS = 
INCS = -I../../include -I. -I.. -I../ctest
CFLAGS = $(INCS) -DTARGET_HOST -g
LDFLAGS = -o $(TARGET_NAME) $(LIBS) -L$(CHECK_LIBDIR)

OBJS = $(SOURCE:.c=.o)
OBJFILES = $(shell echo $(OBJS) | sed 's/\.\.\/\.\.\/drivers\///g' | sed 's/\.\.\/\.\.\/modules\///g' | sed 's/\.\.\/\.\.\/common\///g' | sed 's/\.\.\/ctest\///g' | sed 's/\.\.\///g')

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

doc:
	doxygen

clean:
	rm $(TARGET_NAME) $(OBJFILES)

