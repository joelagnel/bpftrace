argp: $(ANDROID_BUILD_DIR)/argp.done
fetch-sources: argp/sources
remove-sources: remove-argp-sources

# we need to prepare sources of libargp if they are not specified explicitely
ifeq ($(ARGP_SOURCES),)
ARGP_SOURCES = $(abspath argp/sources)
$(ANDROID_BUILD_DIR)/argp: argp/sources
endif

$(ANDROID_BUILD_DIR)/argp.done: $(ANDROID_BUILD_DIR)/argp | $(ANDROID_OUT_DIR)
	cd $(ANDROID_BUILD_DIR)/argp && make -j $(THREADS)
	cp $(ANDROID_BUILD_DIR)/argp/gllib/libargp.a $(ANDROID_OUT_DIR)/lib/.
	cp argp/headers/argp-wrapper.h $(ANDROID_OUT_DIR)/include/argp.h
	cp $(ARGP_SOURCES)/gllib/argp.h $(ANDROID_OUT_DIR)/include/argp-real.h
	touch $@

# generates libargp build files for Android
$(ANDROID_BUILD_DIR)/argp: $(ANDROID_TOOLCHAIN_DIR)
$(ANDROID_BUILD_DIR)/argp: | $(ANDROID_BUILD_DIR)
	-mkdir $@
	cd $@ && $(ARGP_SOURCES)/configure $(ANDROID_EXTRA_CONFIGURE_FLAGS)

# managing the sources of the default argp version
GNULIB_COMMIT_HASH = cd46bf0ca5083162f3ac564ebbdeb6371085df45
GNULIB_REPO = https://git.savannah.gnu.org/git/gnulib.git

argp/sources: | $(DOWNLOADS_DIR)
	-git clone $(GNULIB_REPO) $(DOWNLOADS_DIR)/gnulib
	cd $(DOWNLOADS_DIR)/gnulib && git checkout $(GNULIB_COMMIT_HASH)
	cd $(DOWNLOADS_DIR)/gnulib && ./gnulib-tool --create-testdir \
		--lib="libargp" --dir=$(ARGP_SOURCES) argp

.PHONY: remove-argp-sources
remove-argp-sources:
	rm -rf argp/sources
