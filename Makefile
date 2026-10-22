MODULE_MAIN_OBJ := module.o
MODULE_EXTRA_OBJS := commons/rtc-pcf21xx/pcf21xx.o

SOURCE_DIR := $(if $(src),$(src),$(CURDIR))
include $(SOURCE_DIR)/commons/scripts/kmod-common.mk
