SYSROOT=$(realpath $(dirname $_))

echo "setting up sysroot installed at $SYSROOT"

# links below are required by bcc python library which opens those libs with
# dlopen. Not the best solution but a solution
if [ ! -f $SYSROOT/lib/libbcc.so.0 ]; then
    ln $SYSROOT/lib/libbcc.so -s $SYSROOT/lib/libbcc.so.0
fi
if [ ! -f $SYSROOT/lib/libc.so.6 ]; then
    ln /system/lib64/libc.so -s $SYSROOT/lib/libc.so.6
fi
if [ ! -f $SYSROOT/lib/librt.so.1 ]; then
    ln /system/lib64/libc.so -s $SYSROOT/lib/librt.so.1
fi

export PATH=$SYSROOT/bin:$PATH
export LD_LIBRARY_PATH=$SYSROOT/lib:$LD_LIBRARY_PATH
