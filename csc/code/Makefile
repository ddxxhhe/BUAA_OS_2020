IDIR=../include 
CFLAGS=-I$(IDIR)
_DEPS=fibo.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR=../code
LDIR=csc
LIBS=-lm

_DEPS=fibo.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ=main.o fibo.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)
../fibo: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:clean
clean:
	rm -f *.o
