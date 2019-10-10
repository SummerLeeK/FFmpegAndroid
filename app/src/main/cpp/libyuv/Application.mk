LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := yuv
LOCAL_SRC_FILES := $(LOCAL_PATH)/libyuv.so
include $(PREBUILT_SHARED_LIBRARY)