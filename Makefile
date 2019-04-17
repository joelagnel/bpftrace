# number of threads to use. This value is passed to recursive make calls as -j
# option. To speed up the build invoke make like this: `make THREADS=16`
THREADS ?= 4

BUILD_DIR = build
ANDROID_BUILD_DIR = $(BUILD_DIR)/android
HOST_BUILD_DIR = $(BUILD_DIR)/host
DOWNLOADS_DIR = $(BUILD_DIR)/downloads

OUT_DIR = out
ANDROID_OUT_DIR = $(OUT_DIR)/android
HOST_OUT_DIR = $(OUT_DIR)/host

BASE_NAME = bpftools
VERSION ?= 0.0.1
FULL_NAME = $(BASE_NAME)-$(VERSION)
ARCHIVE_NAME = $(FULL_NAME).tar.gz
ALL_PROJECTS_TARGET = $(FULL_NAME)

all: $(ARCHIVE_NAME)

include toolchain.mk

$(ARCHIVE_NAME): $(FULL_NAME)
	$(TAR) -zcf $@ $(ANDROID_OUT_DIR) --transform="s|$(ANDROID_OUT_DIR)|$(FULL_NAME)|" --owner=0 --group=0

$(FULL_NAME): $(PROJECTS) $(ANDROID_OUT_DIR)/lib/libc++_shared.so
	ln -s $(abspath $(ANDROID_OUT_DIR)) $@

bpftools: $(FULL_NAME)

$(ANDROID_BUILD_DIR) $(HOST_BUILD_DIR) $(DOWNLOADS_DIR):
	mkdir -p $@

 $(ANDROID_OUT_DIR) $(HOST_OUT_DIR):
	mkdir -p $@
	mkdir $@/bin
	mkdir $@/include
	mkdir $@/lib

# we need to copy libc++_shared.so, it's part of the toolchain but it's not
# present on your android system
$(ANDROID_OUT_DIR)/lib/libc++_shared.so: $(ANDROID_TOOLCHAIN_DIR) | $(ANDROID_OUT_DIR)
	find $(ANDROID_TOOLCHAIN_DIR) -name libc++_shared.so -exec cp {} $(ANDROID_OUT_DIR)/lib \;

install: $(ARCHIVE_NAME)
	adb push $(ARCHIVE_NAME) /data/local/tmp
	adb shell "cd /data/local/tmp && tar xf $(ARCHIVE_NAME)"
	adb shell "/data/local/tmp/$(FULL_NAME)/setup.sh"
	adb shell "rm /data/local/tmp/$(ARCHIVE_NAME)"
	@echo "Done ! run adb shell and evaluate setup.sh in current shell to set up environment"
	@echo ". /data/local/tmp/$(FULL_NAME)/setup.sh"

uninstall:
	adb shell "rm -rf /data/local/tmp/$(FULL_NAME)"

clean:
	-rm -fr $(BUILD_DIR)
	-rm -fr $(OUT_DIR)
	-rm -fr $(ANDROID_TOOLCHAIN_DIR)
	-rm $(ARCHIVE_NAME)
	-rm $(FULL_NAME)

.PHONY: clean fetch-sources remove-sources install uninstall
.DELETE_ON_ERROR:

include */build.mk
