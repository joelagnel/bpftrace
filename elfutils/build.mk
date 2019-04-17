$(ALL_PROJECTS_TARGET): elfutils
elfutils: $(ANDROID_BUILD_DIR)/elfutils.done
fetch-sources: elfutils/sources
remove-sources: remove-elfutils-sources

# we need to download sources if source path is not specified
ifeq ($(ELFUTILS_SOURCES),)
ELFUTILS_SOURCES = $(abspath elfutils/sources)
$(ANDROID_BUILD_DIR)/elfutils: elfutils/sources
endif

ELFUTILS_EXTRA_CFLAGS = -I$(abspath $(ANDROID_OUT_DIR)/include)
ELFUTILS_EXTRA_CFLAGS += -I$(abspath elfutils/android_fixups)
ELFUTILS_EXTRA_CFLAGS += -Dprogram_invocation_short_name=\\\"no-program_invocation_short_name\\\"

ELFUTILS_EXTRA_LDFLAGS = -L$(abspath $(ANDROID_OUT_DIR)/lib)
ELFUTILS_EXTRA_ENV_DEFS = CFLAGS="$(ELFUTILS_EXTRA_CFLAGS)" LDFLAGS="$(ELFUTILS_EXTRA_LDFLAGS)"

$(ANDROID_BUILD_DIR)/elfutils.done: $(ANDROID_BUILD_DIR)/elfutils
	cd $(ANDROID_BUILD_DIR)/elfutils/lib && make -j $(THREADS)
	cd $(ANDROID_BUILD_DIR)/elfutils/libelf && make install -j $(THREADS)
	touch $@

# generates libargp build files for Android
$(ANDROID_BUILD_DIR)/elfutils: $(ANDROID_TOOLCHAIN_DIR)
$(ANDROID_BUILD_DIR)/elfutils: argp
$(ANDROID_BUILD_DIR)/elfutils: | $(ANDROID_BUILD_DIR)
	-mkdir $@
	cd $@ && $(ELFUTILS_EXTRA_ENV_DEFS) $(ELFUTILS_SOURCES)/configure \
		$(ANDROID_EXTRA_CONFIGURE_FLAGS)

# managing sources of the default elfutils version
ELFUTILS_VERSION = 0.176
ELFUTILS_URL = http://sourceware.org/pub/elfutils/$(ELFUTILS_VERSION)/elfutils-$(ELFUTILS_VERSION).tar.bz2

elfutils/sources: | $(DOWNLOADS_DIR)
	wget $(ELFUTILS_URL) -O $(DOWNLOADS_DIR)/elfutils-$(ELFUTILS_VERSION).tar.bz2
	-mkdir $@
	$(TAR) xf $(DOWNLOADS_DIR)/elfutils-$(ELFUTILS_VERSION).tar.bz2 -C elfutils/sources \
		--transform="s|^elfutils-$(ELFUTILS_VERSION)||"

remove-elfutils-sources:
	rm -rf elfutils/sources
