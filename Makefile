MODULE_MAIN_OBJ := module.o
COMMON_MODULES := pcf21xx

SOURCE_DIR := $(if $(src),$(src),$(CURDIR))
include $(SOURCE_DIR)/commons/scripts/kmod-common.mk
