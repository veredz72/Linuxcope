
obj-m := Tio.o 

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
INSTALL := ../../install

all:
	make -I../common -C $(KERNELDIR) M=$(PWD)
clean:
	rm -f tio.mod.c *.ko modules.order Module.symvers Module.markers *.o

