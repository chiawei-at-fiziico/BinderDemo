LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_SRC_FILES += $(call all-Iaidl-files-under, src)
LOCAL_PACKAGE_NAME := TrustZoneClient
LOCAL_MODULES_TAGS := optional
LOCAL_SDK_VERSION := current
include $(BUILD_PACKAGE)
