obj-m += simple_char_driver.o

KDIR := /data/srcs/StudyRepos/cpp_study/src_linux_tests/linux_build/linux

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
