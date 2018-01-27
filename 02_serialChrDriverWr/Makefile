CONFIG_MODULE_SIG=n
INSTALL_DIR=modules
ifneq (${KERNELRELEASE},)
	obj-m := myChrDev.o
myChrDev-objs := init.o clean.o openDev.o releaseDev.o readDev.o writeDev.o llseekDev.o trimDev.o

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@rm -rf ${INSTALL_DIR}
	@mkdir ${INSTALL_DIR}
	@mv -f *.o *.ko *.mod.c .*.cmd ${INSTALL_DIR}
clean:
	rm -rf ${INSTALL_DIR}
endif
