obj-m += rtc-pcf2131.o

rtc-pcf2131-objs := rtc-pcf2131-module.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean

install:
	sudo install -m 644 -c rtc-pcf2131.ko /lib/modules/$(shell uname -r)
	sudo depmod
