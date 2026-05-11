MODULE_MAIN_OBJ := module.o

SOURCE_DIR := $(if $(src),$(src),$(CURDIR))
include $(SOURCE_DIR)/commons/scripts/kmod-common.mk
