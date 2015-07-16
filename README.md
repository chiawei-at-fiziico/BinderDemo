This a simple demo of accessing system service from app with binder. App and
service implementations are located under client and server directories
respectively.

In order to build this project, just drop this directory under AOSP tree then
add "trustzone" and "TrustZoneClient" to PRODUCT\_PACKAGES. Don't forget to
include trustzone in init.rc to make it run at boot.
