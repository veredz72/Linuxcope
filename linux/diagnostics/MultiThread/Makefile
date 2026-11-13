
TARGET=x86_64-redhat-linux
OBJ_DIR = $(TARGET)

OBJS 		= $(TARGET)/Main.o\

CC = gcc
INCLUDES 	= -I../../library/Tio\
	          -I../../library/Linuxcope

CFLAGS		= -g $(INCLUDES) 

LD          = $(CC)
LIBS =		-lpthread \
		-L../../release/$(TARGET) -lTio \
		-L../../release/$(TARGET) -lLinuxcope \
	

pre-build: 	check_objectdir target

target: $(OBJS)
	make -C ../../library/Tio
	make -C ../../library/Linuxcope
	make -C ../../driver/Tio
	make -C ../../driver/Linuxcope 
	$(LD) $(LDFLAGS) $(CFLAGS) $(OBJS) $(LIBS) -o Main.out 
		
check_objectdir :
	@if [ ! -d "$(TARGET)" ]; then\
		mkdir -p $(TARGET);\
	fi
		
$(TARGET)/Main.o: Main.c 
	$(CC) $(INCLUDES) $(CFLAGS) -c Main.c -o $(TARGET)/Main.o

clean:
	make -C ../../library/Tio clean
	make -C ../../library/Linuxcope clean
	make -C ../../driver/Tio clean
	make -C ../../driver/Linuxcope clean
	rm -Rf $(TARGET)
	rm Main.out
