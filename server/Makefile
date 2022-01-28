CC = clang
CFLAGS = -std=gnu11 -pthread -g 
# -Wall -Wextra -Werror -Wpedantic
# CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -pthread -g

OBJDIR = obj
SRCDIR = src src/api src/server_utils src/database
SRVR_UTILS_DIR = ../server_utils
UCHAT = ../uchat_server

SRC = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
OBJS = $(OBJDIR)/*.o

LIBMX_DIR = ../libraries/libmx
LIBMX_NAME = $(LIBMX_DIR)/libmx.a

UTILSLIB_DIR = ../utils
UTILSLIB_NAME = $(UTILSLIB_DIR)/utilslib.a

CJSON_DIR = ../libraries/cjson
CJSON_NAME = $(CJSON_DIR)/libcjson.a

SSL_DIR = ../libraries/openssl
SSL_FILES:= ../local_lib/lib
SSL_INC_FILES:= $(SSL_DIR)

LIB_FLAGS = -lmx -lcjson -lsqlite3 -lssl -lcrypto \
			-L$(LIBMX_DIR) $(LIBMX_NAME) \
			-L$(UTILSLIB_DIR) $(UTILSLIB_NAME) \
			-L$(CJSON_DIR) $(CJSON_NAME) \
			# -L$(SSL_FILES) -I$(SSL_INC_FILES)

all: $(UCHAT)

$(UCHAT):
	mkdir $(SRVR_UTILS_DIR)
	mkdir $(OBJDIR)
	$(CC) $(CFLAGS) -c $(SRC)
	mv *.o $(OBJDIR)
	$(CC) $(CFLAGS) -o $(UCHAT) $(OBJS) $(LIB_FLAGS)

clean:
	rm -f $(OBJS)
	rm -df $(OBJDIR)
	rm -rdf $(SRVR_UTILS_DIR)

uninstall:
	make clean
	rm -f $(UCHAT)

reinstall:
	make uninstall
	make all
