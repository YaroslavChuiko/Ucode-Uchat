CC = clang
CFLAGS = -std=gnu11 -Wall -Wextra -Werror -Wpedantic
# CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

OBJDIR = obj
SRCDIR = src
LIBNAME = utilslib.a
LIB = UTILSLIB

SRC = $(SRCDIR)/*.c
OBJS = $(OBJDIR)/*.o

all: $(LIB)

$(LIB):
	mkdir $(OBJDIR)
	$(CC) $(CFLAGS) -c $(SRC)
	mv *.o $(OBJDIR)
	ar rcs $(LIBNAME) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -df $(OBJDIR)

uninstall:
	make clean
	rm -f $(LIBNAME)

reinstall:
	make uninstall
	make all