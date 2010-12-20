
# Konfiguration des Projekte verwenden
include ../config.mk

# Source-Code Dateien
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

# Wie heisst unser ausführbares Assembly?
TARGET_NAME = test_main

# Welche Bibliotheken benötigen wird
LIBS = 

# Verschiedene Include-Verzeichnisse
INCS = -I../include -I. -Ictest

# Flags für den Compiler
CFLAGS = $(INCS) -DTARGET_HOST -g

# Flags für den Linker
LDFLAGS = -o $(TARGET_NAME) $(LIBS)

# Alle Objekt-Dateien sind alle Code-Dateien nur mit der Endung .o
OBJS = $(SOURCE:.c=.o)

# Manche Code-Dateien haben als Prefix einen Pfad, diesen dürfen wir nicht für die
# Objektdateien übernehmen, da die Objektdateien im tests/ Ordner abgelegt werden und
# sollte der Pfad noch im Namen der Objektdatei enthalten sein, dann wird sie vom
# Compiler/Linker nicht gefunden.
OBJFILES = $(shell echo $(OBJS) | sed 's/\.\.\/drivers\///g' | sed 's/\.\.\/modules\///g' | sed 's/ctest\///g')

# Aktuelles Test-Datum ermitteln
TEST_DATE = $(shell echo `date +%Y%m%d%H%M`)

all: build run

# Abhängigkeit von allen Objekt-Dateien, sind diese vorhanden wird das Assembly erstellt
build: $(OBJS)
	gcc $(LDFLAGS) $(OBJFILES)

# Erstellen der Objekt-Dateien aus den Code-Dateien
%.o: %.c 
	$(CC_HOST) -c $< $(CFLAGS)

# Ausführen der Unit-Tests
run: 
	./$(TARGET_NAME) --test-date='$(TEST_DATE)'

# Dokumentation erstellen
doc:
	doxygen

# Aufräumen
clean:
	rm -rf $(TARGET_NAME) $(OBJFILES)

