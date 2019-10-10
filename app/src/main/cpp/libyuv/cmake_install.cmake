# Install script for directory: /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/libyuv.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyuv.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyuv.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyuv.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libyuv" TYPE FILE FILES
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/basic_types.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/compare.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/convert.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/convert_argb.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/convert_from.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/convert_from_argb.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/cpu_id.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/planar_functions.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/rotate.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/rotate_argb.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/row.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/scale.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/scale_argb.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/scale_row.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/version.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/video_common.h"
    "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv/mjpeg_decoder.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/include/libyuv.h")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
