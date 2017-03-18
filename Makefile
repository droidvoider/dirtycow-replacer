ARCH := $(shell adb shell getprop ro.product.cpu.abi)
SDK_VERSION := $(shell adb shell getprop ro.build.version.sdk)

all: build

build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk APP_ABI=$(ARCH) APP_PLATFORM=android-$(SDK_VERSION)

log: 
	adb logcat | grep -a dirty-replacer

push: build 
	adb push files.txt /data/local/tmp/files.txt
	adb push replace/ /data/local/tmp/
	adb push replacewith/ /data/local/tmp/
	adb push libs/$(ARCH)/replacer /data/local/tmp/replacer
	adb shell chmod 0777 /data/local/tmp/replacer

clean:
	rm -rf libs
	rm -rf obj

