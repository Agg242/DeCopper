CC=vc
CFLAGS+= -IFiles:dev/c/lib/tools -c99 -+ -dontwarn=214
LDFLAGS += -lamiga -lauto

SOURCES=main.c decop.c
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

EXE=main


.PHONY: all clean

all: clist.o decopper

decopper:   $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	@-delete  DBGEXE) $(DBGOBJS) ALL QUIET
