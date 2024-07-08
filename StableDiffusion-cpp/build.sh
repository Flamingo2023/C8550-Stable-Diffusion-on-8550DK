#!/bin/bash

rm -r release
rm StableDiffusion_C8550_qnn-2.14.tar.gz
mkdir release
mkdir -p release/libs
mkdir -p release/models
mkdir -p release/models/utils

rm -r build
mkdir build
pushd build
cmake ../
make -j6
popd
cp build/stablediffusion release/
cp models/*.bin release/models/
cp models/*.txt release/models/utils/
cp 3rd/libs/opencv/* release/libs/

pushd release/libs/
ln -s libopencv_core.so.4.5.5 libopencv_core.so.405
ln -s libopencv_core.so.4.5.5 libopencv_core.so
ln -s libopencv_imgcodecs.so.4.5.5 libopencv_imgcodecs.so.405
ln -s libopencv_imgcodecs.so.4.5.5 libopencv_imgcodecs.so
ln -s libopencv_imgproc.so.4.5.5 libopencv_imgproc.so.405
ln -s libopencv_imgproc.so.4.5.5 libopencv_imgproc.so
popd

# libQnnHtp.so libQnnHtpV73Stub.so libQnnSystem.so
cp 3rd/qnn/2.14.0.230828/lib/aarch64-oe-linux-gcc11.2/libQnnHtp.so        release/libs/
cp 3rd/qnn/2.14.0.230828/lib/aarch64-oe-linux-gcc11.2/libQnnHtpV73Stub.so release/libs/
cp 3rd/qnn/2.14.0.230828/lib/aarch64-oe-linux-gcc11.2/libQnnSystem.so     release/libs/

tar -czvf StableDiffusion_C8550_qnn-2.14.tar.gz release
