
CC := /opt/toolchains/dstwo
CURR_DIR = ${shell pwd}

all: $(CC)


$(CC):
	mkdir -p /opt
	cd /opt;tar -xjf $(CURR_DIR)/dstwo-toolchain.tar.bz2
	chmod a+rwx $(CURR_DIR)/../tools/makeplug.exe
	chmod a+rwx $(CURR_DIR)/../tools/decryptplug.exe

