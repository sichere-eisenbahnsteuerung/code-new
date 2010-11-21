
NULL = 

CROSS = wine ~/.wine/drive_c/Keil/C51/BIN

MAKE = make
CC = $(CROSS)/C51.exe
AS = $(CROSS)/A51.exe
LD = $(CROSS)/BL51.exe
HEX = $(CROSS)/OH51.exe
SREC_CAT = srec_cat
SPLINT = splint


BUILDDIR = tmp
OBJDIR = $(BUILDDIR)/obj
LSTDIR = $(BUILDDIR)/lst
IMAGEDIR = $(BUILDDIR)/image

CFLAGS = \
	LARGE "OPTIMIZE(9,SPEED)" \
	"INCDIR(sysinc;private)" \
	"PRINT($(LSTDIR)/$$(basename $< .c).lst)" \
	"OBJECT($(OBJDIR)/$$(basename $< .c).obj)") \
	CODE LISTINCLUDE SYMBOLS

AFLAGS = \
	NOMOD51 SET "(LARGE,BootBlock=0)" \
	"PRINT($(LSTDIR)/$$(basename $< .a51).lst)" \
	"OBJECT($(OBJDIR)/$$(basename $< .a51).obj)" \
	EP

LDFLAGS = \
	TO $(IMAGEDIR)/$(TARGET).obj \
	CODE(0x0000-0xf3ff) \
	XDATA(0xf400-0xfbff) \
	DISABLEWARNING (16)

SPLINTFLAGS =

TARGET = ses_image

XRAM_LOCATION = 0xf400
XRAM_SIZE = 2048
# FIXME whats that?
IRAM_SIZE = 256
CODE_SIZE = 0xf400
