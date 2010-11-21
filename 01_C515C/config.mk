
NULL = 

CROSS = wine ~/.wine/drive_c/Keil/C51/BIN

MAKE = make
CC_TARGET = $(CROSS)/C51.exe
AS_TARGET = $(CROSS)/A51.exe
LD_TARGET = $(CROSS)/BL51.exe
HEX_TARGET = $(CROSS)/OH51.exe
CC_HOST = gcc
SREC_CAT = srec_cat
SPLINT = splint

SPLINTFLAGS =

TARGET = ses_image
