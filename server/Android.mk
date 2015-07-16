LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := trustzone
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := trustzone.cpp
LOCAL_SHARED_LIBRARIES := libutils libcutils libbinder
LOCAL_C_INCLUDES += frameworks/base/include system/core/include
include $(BUILD_EXECUTABLE)
