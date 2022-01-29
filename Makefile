OBJDIR = obj
SRCDIR = src
SERVER_DIR = server
CLIENT_DIR = client
SERVER = uchat_server
CLIENT = uchat

LIBMX_DIR = libraries/libmx
LIBMX = $(LIBMX_DIR)/libmx.a

UTILSLIB_DIR = utils
UTILSLIB = $(UTILSLIB_DIR)/utilslib.a

CJSON_DIR = libraries/cjson
CJSON = $(CJSON_DIR)/libcjson.a

SQLITE_DIR = libraries/sqlite
SQLITE = $(SQLITE_DIR)/libsqlite3.a

SRC = $(SRCDIR)/*.c
OBJS = $(OBJDIR)/*.o

all: $(LIBMX) $(UTILSLIB) $(CJSON) $(SQLITE) $(SERVER) $(CLIENT)

$(LIBMX):
	# make -sC $(LIBMX_DIR)

$(UTILSLIB):
	make -sC $(UTILSLIB_DIR)

$(CJSON):
	# make -sC $(CJSON_DIR)

$(SQLITE):
	# make -sC $(SQLITE_DIR)

$(SERVER):
	make -sC $(SERVER_DIR)

$(CLIENT):
	make -sC $(CLIENT_DIR)

clean:
	rm -f $(OBJS)
	rm -df $(OBJDIR) 

uninstall:
	make -sC $(SERVER_DIR) $@
	make -sC $(CLIENT_DIR) $@
	make -sC $(UTILSLIB_DIR) $@
	# make -sC $(LIBMX_DIR) $@
	# make -sC $(CJSON_DIR) $@
	# make -sC $(SQLITE_DIR) $@
	make clean
	rm -f $(UCHAT)

reinstall:
	make uninstall
	make all
