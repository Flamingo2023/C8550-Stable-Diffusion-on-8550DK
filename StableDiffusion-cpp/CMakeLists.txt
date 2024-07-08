cmake_minimum_required(VERSION 3.18.1)
project("StableDiffusion")

include_directories(
	${CMAKE_SOURCE_DIR}/include/
	${CMAKE_SOURCE_DIR}/include/opencv/
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/Utils 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/Log 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/PAL/include 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/WrapperUtils 
	${CMAKE_SOURCE_DIR}/3rd/qnn/2.14.0.230828/include/QNN/
)

file(GLOB SRC 
	${CMAKE_SOURCE_DIR}/src/*.cpp 
	${CMAKE_SOURCE_DIR}/src/scheduler/*.cpp 
	${CMAKE_SOURCE_DIR}/src/utils/*.cpp 
	${CMAKE_SOURCE_DIR}/src/models/*.cpp 
	${CMAKE_SOURCE_DIR}/src/qcom/QCOMModel.cpp 
	${CMAKE_SOURCE_DIR}/src/qcom/time_all.cpp
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/PAL/src/common/GetOpt.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/PAL/src/common/StringOp.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/PAL/src/linux/Directory.cpp
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/PAL/src/linux/DynamicLoading.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/PAL/src/linux/FileOp.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/PAL/src/linux/Path.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/Log/Logger.cpp
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/Log/LogUtils.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/Utils/DataUtil.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/Utils/DynamicLoadUtil.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/Utils/IOTensor.cpp 
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/Utils/QnnSampleAppUtils.cpp
	${CMAKE_SOURCE_DIR}/include/qnnUtils_8550/WrapperUtils/QnnWrapperUtils.cpp
)

add_executable(stablediffusion
	${SRC}
)

target_link_libraries(stablediffusion
	${CMAKE_SOURCE_DIR}/3rd/libs/opencv/libopencv_core.so.4.5.5
	${CMAKE_SOURCE_DIR}/3rd/libs/opencv/libopencv_imgcodecs.so.4.5.5
	${CMAKE_SOURCE_DIR}/3rd/libs/opencv/libopencv_imgproc.so.4.5.5
	z
)