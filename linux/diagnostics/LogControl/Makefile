
TARGET=x86_64-redhat-linux
OBJ_DIR = $(TARGET)

OBJS 		= $(TARGET)/Main.o\

CC = gcc
INCLUDES 	= -I../../library/LinuxcopeAdmin

CFLAGS		= -g $(INCLUDES) 

LD          = $(CC)
LIBS =		-L../../release/$(TARGET) -lLinuxcopeAdmin \
	

pre-build: 	check_objectdir target

target: $(OBJS)
	make -C ../../library/LinuxcopeAdmin
	$(LD) $(LDFLAGS) $(CFLAGS) $(OBJS) $(LIBS) -o Main.out 
		
check_objectdir :
	@if [ ! -d "$(TARGET)" ]; then\
		mkdir -p $(TARGET);\
	fi
		
$(TARGET)/Main.o: Main.c 
	$(CC) $(INCLUDES) $(CFLAGS) -c Main.c -o $(TARGET)/Main.o

clean:
	make -C ../../library/LinuxcopeAdmin clean
	rm -Rf $(TARGET)
	rm Main.out
