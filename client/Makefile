CC = clang
CFLAGS = -std=gnu11 -pthread -g 
# -Wall -Wextra -Werror -Wpedantic
# CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -pthread -g

UTIL_DIRS = logs data/avatars
OBJDIR = obj
SRCDIR = src src/request_handlers src/gui
UCHAT = ../uchat

SRC = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
OBJS = $(OBJDIR)/*.o

LIBMX_DIR = ../libraries/libmx
LIBMX_NAME = $(LIBMX_DIR)/libmx.a

UTILSLIB_DIR = ../utils
UTILSLIB_NAME = $(UTILSLIB_DIR)/utilslib.a

CJSON_DIR = ../libraries/cjson
CJSON_NAME = $(CJSON_DIR)/libcjson.a

GTK_FLAGS = `pkg-config --cflags gtk+-3.0`
GTK_LIBS_FLAGS = `pkg-config --cflags --libs gtk+-3.0`

SSL_DIR = ../libraries/openssl
SSL_FILES:= ../local_lib/lib
SSL_INC_FILES:= $(SSL_DIR)

LIB_FLAGS = -lmx -lcjson -lsqlite3 -lssl -lcrypto\
			-L$(UTILSLIB_DIR) $(UTILSLIB_NAME)\
			-L$(LIBMX_DIR) $(LIBMX_NAME)\
			-L$(CJSON_DIR) $(CJSON_NAME)\
			# -L$(SSL_FILES) -I$(SSL_INC_FILES)

all: $(UCHAT)

$(UCHAT):
	mkdir $(UTIL_DIRS) $(OBJDIR)
	$(CC) $(CFLAGS) $(GTK_FLAGS) -c $(SRC)
	mv *.o $(OBJDIR)
	$(CC) $(CFLAGS) $(GTK_LIBS_FLAGS) -o $(UCHAT) $(OBJS) $(LIB_FLAGS)

clean:
	rm -f $(OBJS)
	rm -rdf $(UTIL_DIRS) $(OBJDIR)

uninstall:
	make clean
	rm -f $(UCHAT)

reinstall:
	make uninstall
	make all
