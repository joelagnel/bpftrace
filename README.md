# Building bpftrace and bcc for Android
This branch contains set of makefiles preparing custom sysroot for Android containing bpftrace, bcc and few other tools which you can just copy over to your phone.

## Requirements
Makefiles in this branch make use of the following tools on the build machine:
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
- gnu tar
- bison

To run bpftrace and bcc you'll also need a device running Linux kernel providing required functionality (see "Linux Kernel Requirements" section [here](https://github.com/iovisor/bpftrace/blob/master/INSTALL.md#linux-kernel-requirements)). In case of arm64 it's great if the device runs kernel version 4.10+ ([that's when uprobe support for arm64 was landed](https://github.com/torvalds/linux/commit/9842ceae9fa8deae141533d52a6ead7666962c09)).

## Usage
The following builds and copies a sysroot directory containing bpftrace, bcc, python and their dependencies to your android device under `/data/local/tmp/bpftools-0.0.1`:

```bash
make THREADS=8 NDK_PATH=<path to android-ndk-r17>
make install
```

In order to use bpftrace you need to tell your adb shell session where to find all the executables and libs. You can set `PATH` and `LD_LIBRARY_PATH` on your own or just source `setup.sh` script.

Inside `adb shell` run:
```bash
. /data/local/tmp/bpftools-0.0.1/setup.sh
```

The script takes care of creating some additional symlinks that will make bcc's python frontend happy.

If you intend to peek at kernel data structures you'll need to make kernel headers available to bpftrace. Copy them to the device and export two more shell variables:
```bash
export ARCH=arm64
export BPFTRACE_KERNEL_SOURCE=<path to kernel headers>
```

## Getting bpftrace to work on Google Pixel2
In order to use bpftrace on Google Pixel2 you need to install system image allowing for root access and running kernel supporting bpf instrumentation. Default kernels included in AOSP repos won't do as Pixel2 uses kernel 4.4. I created a fork of kernel 4.4 supporting kprobe and tracepoint providers (TODO: uprobe) and you can use it with Pixel2 images based on `android-9.0.0_r35`. You can find it [here](https://github.com/michalgr/kernel_msm/tree/basic_bpf_tracing_pixel2).

A handful of links that might be usefull when getting Pixel2 ready:
- [it might be quite difficult to get a Pixel2 phone with unlockable bootloader](https://forum.xda-developers.com/pixel-2/help/oem-unlocking-grayed-vzw-pixel-2-t3776763), perhaps XL variant is easier to get
- [instructions for building AOSP](https://source.android.com/setup/build/requirements)
- [instructions for building Kernel for Android](https://source.android.com/setup/build/building-kernels)

## Included projects
Makefiles included in this branch fetch sources of and cross compile following projects:
- [bpftrace](https://github.com/iovisor/bpftrace)
- [bcc](https://github.com/iovisor/bcc)
- [python](https://github.com/python/cpython)
- [llvm + clang](https://github.com/llvm/llvm-project)
- [flex](https://github.com/westes/flex)
- [elfutils](https://sourceware.org/elfutils/)
- [argp (part of gnulib)](https://www.gnu.org/software/gnulib/)

Here is the topology:

![dependencies](imgs/deps.svg)

## Android ndk requirement
You need Android ndk new enough to target API level 28 but old enough to still contain gcc (in newer ndks gcc was dropped and all binaries looking like gcc are fancy named clang). We need gcc because elfutils demands that provided c compiler understands nested functions (and clang does not). Ndk r17c is ok.

## Building bcc
Master of bcc requires uapi headers which are not available in the ndk. As a short term-workaround we pull in a fork based on a revision that does not require new headers: https://github.com/michalgr/bcc/tree/compile-for-android 