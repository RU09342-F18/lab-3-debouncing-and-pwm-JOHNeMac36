PROJECT_NAME=software_pwm
BOARD=msp430f5529
TARGET=$(BOARD)_$(PROJECT_NAME).elf

CC=msp430-elf-gcc
CFLAGS=-mmcu=$(BOARD) -Wall
MSP430_SUPPORT_FILES_INCLUDE=/opt/msp430-gcc-support-files/include

SRCDIR=src
BINDIR=bin

SOURCES:=$(wildcard $(SRCDIR)/*.c)
INCLUDES:=-I$(MSP430_SUPPORT_FILES_INCLUDE)

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(BINDIR)/$(TARGET)
	@echo "make completed"

run:
	@echo "mspdebug tilib "prog $(BINDIR)/$(TARGET)""
	@mspdebug tilib "prog $(BINDIR)/$(TARGET)"

clean:
	@rm $(BINDIR)/* || true
