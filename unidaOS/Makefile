DL := f

CROSS := /opt/toolchains/dstwo/bin/
MKPLG := ../tools/makeplug.exe

CC = $(CROSS)mipsel-linux-gcc
AR = $(CROSS)mipsel-linux-ar cr
LD	= $(CROSS)mipsel-linux-ld
OBJCOPY	= $(CROSS)mipsel-linux-objcopy
NM	= $(CROSS)mipsel-linux-nm
OBJDUMP	= $(CROSS)mipsel-linux-objdump

TOPDIR = .
SRC_DIR = $(TOPDIR)/src
FS_DIR = $(TOPDIR)/../libsrc/fs
CONSOLE_DIR = $(TOPDIR)/../libsrc/console
KEY_DIR = $(TOPDIR)/../libsrc/key

LIB_SRC_DIR := $(TOPDIR)/libunida
#LIB_OBJS := $(LIB_SRC_DIR)/unida.o, $(LIB_SRC_DIR)/unida_fs.o
#LIB_SRCS := $(LIB_SRC_DIR)/unida.c, $(LIB_SRC_DIR)/unida_fs.c

SRC := $(SRC_DIR)/ds2_main.c
SSRC :=

LIBS := ./lib/libds2a.a ./lib/libds2b.a ./lib/libunida.a -lc -lm -lgcc

INC := -I./include -I../include -I$(FS_DIR) -I$(CONSOLE_DIR) -I$(KEY_DIR)

CFLAGS := -mips32 -O3 -mno-abicalls -fno-pic -fno-builtin -fno-exceptions -ffunction-sections -mlong-calls -fomit-frame-pointer -msoft-float -G 4

LINKS := ../specs/link.xn
STARTS := ../specs/start.S
STARTO := start.o

#OBJS	:= $(addsuffix .o , $(basename $(notdir $(SRC))))
#SOBJS	:= $(addsuffix .o , $(basename $(notdir $(SSRC))))
OBJS	:= $(SRC:.c=.o)
SOBJS	:= $(SSRC:.S=.o)

NME	:= unidaOS
APP	:= ./bin/$(NME).elf

deploy: rebuild copy

copy:
	cp -axv data/./ /cygdrive/$(DL)/_dstwoplug/

rebuild: clean all

all: lib $(APP)
	$(OBJCOPY)  -O binary $(APP) 	./bin/$(NME).bin
	$(OBJDUMP)  -d $(APP) > 	 	./bin/$(NME).dump
	$(NM) 		$(APP) | sort >  	./bin/$(NME).sym
	$(OBJDUMP)  -h $(APP) > 	 	./bin/$(NME).map
	$(MKPLG) 	./bin/$(NME).bin 	./data/$(NME).plg

lib: unida.o unida_fs.o
	$(AR) libunida.a unida.o unida_fs.o
	mv unida.o unida_fs.o lib && cp libunida.a lib/libunida.a && mv libunida.a libunida/overwrite_backup_libunida.a

$(APP):	depend $(SOBJS) $(OBJS) $(STARTO) $(LINKS)
	$(CC) -nostdlib -static -T $(LINKS) -o $@ $(STARTO) $(SOBJS) $(OBJS) $(LIBS)

$(STARTO):
	$(CC) $(CFLAGS) $(INC) -o $@ -c $(STARTS)

unida.o:
	$(CC) $(INC) -c $(LIB_SRC_DIR)/unida.c

unida_fs.o:
	$(CC) $(INC) -c $(LIB_SRC_DIR)/unida_fs.c

.c.o:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
.cpp.o:
	$(CC) $(CFLAGS) $(INC) -fno-rtti -fvtable-gc -o $@ -c $<
.S.o:
	$(CC) $(CFLAGS) $(INC) -D_ASSEMBLER_ -D__ASSEMBLY__ -o $@ -c $<

clean:
	rm -fr *.o $(OBJS) $(OTHER) bin/$(NME).* ./libunida/*.o ./lib/libunida.a
	rm depend

depend:	Makefile
	$(CC) -MM $(CFLAGS) $(INC) $(SSRC) $(SRC) > $@

sinclude depend
