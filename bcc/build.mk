bcc: $(ANDROID_BUILD_DIR)/bcc.done
fetch-sources: bcc/sources
remove-sources: remove-bcc-sources

# we need to download sources if source path is not specified
ifeq ($(BCC_SOURCES),)
BCC_SOURCES = $(abspath bcc/sources)
$(ANDROID_BUILD_DIR)/bcc: bcc/sources
endif

# builds and installs bcc for Android.
$(ANDROID_BUILD_DIR)/bcc.done: $(ANDROID_BUILD_DIR)/bcc
	cd $(ANDROID_BUILD_DIR)/bcc && $(MAKE) install -j $(THREADS)
	touch $@

# generates bcc build files for Android
$(ANDROID_BUILD_DIR)/bcc: llvm flex elfutils
$(ANDROID_BUILD_DIR)/bcc: $(HOST_OUT_DIR)/bin/flex
$(ANDROID_BUILD_DIR)/bcc: $(ANDROID_CMAKE_DEPS)
$(ANDROID_BUILD_DIR)/bcc: | $(ANDROID_BUILD_DIR)
	-mkdir $@
	cd $@ && CXXFLAGS="$(ANDROID_CMAKE_CXXFLAGS)" LDFLAGS="$(ANDROID_CMAKE_LDFLAGS)" \
		$(CMAKE) $(BCC_SOURCES) \
		$(ANDROID_EXTRA_CMAKE_FLAGS) \
		-DFLEX_EXECUTABLE=$(abspath $(HOST_OUT_DIR)/bin/flex) \
		-DPYTHON_CMD=python3.6

# managing sources of the default python version
BCC_BRANCH_OR_TAG = compile-for-android
BCC_REPO = https://github.com/michalgr/bcc.git

bcc/sources:
	git clone $(BCC_REPO) bcc/sources --depth=1 -b $(BCC_BRANCH_OR_TAG)

.PHONY: remove-bcc-sources
remove-bcc-sources:
	rm -rf bcc/sources
