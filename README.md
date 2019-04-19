# Building bpftrace and bcc for Android
This branch contains makefiles preparing custom sysroot for Android containing:
- [bpftrace](https://github.com/iovisor/bpftrace)
- [bcc](https://github.com/iovisor/bcc)
- [python](https://github.com/python/cpython)
- [llvm + clang](https://github.com/llvm/llvm-project)
- [flex](https://github.com/westes/flex)
- [elfutils](https://sourceware.org/elfutils/)
- [argp (part of gnulib)](https://www.gnu.org/software/gnulib/)

![dependencies between projects](imgs/deps.svg)

## Requirements
Following tools need to be available on the build machine:
- ndk supporting API level 28 and containing gcc (r17c)
- make
- cmake
- autoconf
- automake
- libtool
- help2man
- git
- wget
- sed
- tar (gtar on mac)
- bison

Host machine needs to run
- Android 9+
- Linux kernel supporting bpf tracing, see [Kernel requirements](#Kernel-requirements)

## Usage
Following commands build and copy custom sysroot to connected Android device under `/data/local/tmp/bpftools-0.0.1`:

```bash
make THREADS=8 NDK_PATH=<path to android-ndk-r17>
make install
```

In order to make bpftrace available in current `adb shell` session you need to set `PATH` (`/data/local/tmp/bpftools-0.0.1/bin`) and `LD_LIBRARY_PATH` (`/data/local/tmp/bpftools-0.0.1/lib`) environment variables. This is automated by `setup.sh` script which you can source instead setting vars by hand. The script also takes care of creating symlinks inside `/data/local/tmp/bpftools-0.0.1/lib` making some libraries available under names expected by bcc's python frontend.

Inside `adb shell` run:
```bash
. /data/local/tmp/bpftools-0.0.1/setup.sh
```

In order to enable bpftrace to operate on kernel data structures you need to tell it where to look for kernel headers. Copy them to a directory on the device and set `BPFTRACE_KERNEL_SOURCE` to point to that directory. In addition you might be required to help bpftrace recognize the architecture by setting ARCH environment variable:
```bash
export ARCH=arm64
export BPFTRACE_KERNEL_SOURCE=<path to kernel headers>
```

## Kernel requirements
bpftrace depends on functionality added to Linux during 4.x series development. Documentation of those features and corresponding minimal versions can be found in [bpftrace](https://github.com/iovisor/bpftrace/blob/master/INSTALL.md#linux-kernel-requirements) and [bcc](https://github.com/iovisor/bcc/blob/master/INSTALL.md#kernel-configuration) repos. Some of that code is architecture specific, you need to take that into account when choosing kernel. In case of arm64 version 4.10+ is a good choice ([that's when uprobe support for arm64 was landed](https://github.com/torvalds/linux/commit/9842ceae9fa8deae141533d52a6ead7666962c09)).

When building custom kernel for Android the following resources might provide help:
- [instructions for building AOSP](https://source.android.com/setup/build/requirements)
- [instructions for building Kernel for Android](https://source.android.com/setup/build/building-kernels)

## Getting bpftrace to work with Google Pixel 2 (Linux 4.4)
Google Pixel 2 runs Linux version 4.4 which severely limits capabilities of bpftrace. You can work around that by using [this fork](https://github.com/michalgr/kernel_msm/tree/basic_bpf_tracing_pixel2) instead of default kernel available in AOSP. The fork is based on Android's `android-9.0.0_r35` tag and contains number of backported changes enabling kprobe and tracepoint providers, as well as bringing number of bpf helper functions.

**TODO**: as of now the fork does not support arm64 uprobes.
## Android ndk requirement (r17c)
Build scripts in this repo target API level 28. At the same time, elfutils demands that provided c compiler understands nested functions, which clang does not. Unfortunately gcc in ndk was deprecated and removed in r18b. The only ndk satisfying all the conditions is r17c.

## Building bcc
Master of bcc requires uapi headers which are not available in ndk r17c. As a short term-workaround build scripts download and build a fork based on a revision that does not require new headers: https://github.com/michalgr/bcc/tree/compile-for-android.