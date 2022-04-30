SRC = ./src/wavfile/wavfile.c \
	./src/sample.c
	
OUT = bin

SAMPLE = $(OUT)/sample

ASSETS = assets
	
INCLUDES = -I./src/wavfile \
	-I./libpd/libpd_wrapper \
	-I./libpd/pure-data/src
	
LIBS = -L./libpd/libs -lpd

CFLAGS = $(INCLUDES)

ifeq ($(shell uname),Darwin)
	LIB_DIR = libs/
	SOLIB_PREFIX = lib
	SOLIB_EXT = dylib
else
	LIB_DIR = 
	SOLIB_PREFIX =
	SOLIB_EXT = dll
	LDFLAGS += -Wl,--export-all-symbols \
		-static-libgcc
endif

LDFLAGS += $(LIBS)

LIBPD_DIR = libpd
LIBPD_FLAGS = MULTI=true FAT_LIB=true EXTRA=false
LIBPD = $(LIBPD_DIR)/libs/$(SOLIB_PREFIX)pd.$(SOLIB_EXT)
LIBPD_LOCAL = $(OUT)/$(LIB_DIR)$(SOLIB_PREFIX)pd.$(SOLIB_EXT)

ifeq ($(OS),Windows_NT)
	LIBPD_FLAGS += ADDITIONAL_CFLAGS='-DPD_LONGINTTYPE="long long"'
endif

$(SAMPLE): ${SRC:.c=.o} $(LIBPD_LOCAL)
	$(CC) -o $@ ${SRC:.c=.o} $(LDFLAGS)
	cp assets/* $(OUT)

$(LIBPD_LOCAL): Makefile.patch $(OUT) $(LIB_DIR)
ifeq ($(OS),Windows_NT)
	patch -u $(LIBPD_DIR)/Makefile $<
endif
	$(MAKE) -C $(LIBPD_DIR) $(LIBPD_FLAGS)
	cp $(LIBPD) $@

$(OUT):
	mkdir $@

$(LIB_DIR): $(OUT)
	mkdir $(OUT)/$@

clean:
	rm -r $(OUT)
	rm ${SRC:.c=.o}
