CC = clang
# CFLAGS = -std=gnu11 -Wall -Wextra -Werror -Wpedantic
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

OBJDIR = obj
SRCDIR = src src/db_lists
LIBNAME = utilslib.a
LIB = UTILSLIB

LIBMX_DIR = ../libraries/libmx
LIMBX_INCS = $(LIBMX_DIR)/inc
LIBMX_NAME = $(LIBMX_DIR)/libmx.a

SRC = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
OBJS = $(OBJDIR)/*.o

LIB_FLAGS = -I$(LIMBX_INCS)

all: $(LIB)

$(LIB):
	mkdir $(OBJDIR)
	$(CC) $(CFLAGS) -c $(SRC) $(LIB_FLAGS)
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
