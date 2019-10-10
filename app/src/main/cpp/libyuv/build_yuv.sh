ARCH=arm
ANDROID_ARCH_ABI=armeabi-v7a
NDK_PATH=/Users/apple/Downloads/android-ndk-r16b
PREFIX=`pwd`/android/${ARCH}/${CPU}

# cmake 传参
/Users/apple/Library/Android/sdk/cmake/3.10.2.4988404/bin/cmake -G"Unix Makefiles" \
	-DANDROID_NDK=${NDK_PATH} \
    -DCMAKE_TOOLCHAIN_FILE=${NDK_PATH}/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=${ANDROID_ARCH_ABI} \
    -DANDROID_NATIVE_API_LEVE=16 \
    -DCMAKE_INSTALL_PREFIX=${PREFIX} \
	-DANDROID_ARM_NEON=TRUE \
    ..
    
# 生成动态库
make 
make install
