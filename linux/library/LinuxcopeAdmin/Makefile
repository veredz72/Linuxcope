
TARGET = x86_64-redhat-linux

CP = cp
RM = rm
CCFLAGS =  -g 
ARFLAGS = -q

RELEASE = ../../release/$(TARGET)

OBJS = \
	$(TARGET)/LinuxcopeAdmin.o 

pre-build: 	check_objectdir target

target: $(OBJS) $(RELEASE) $(TARGET)
	$(AR) $(ARFLAGS) $(TARGET)/libLinuxcopeAdmin.a $(OBJS)
	$(CP) $(TARGET)/libLinuxcopeAdmin.a $(RELEASE)
	$(CP) LinuxcopeAdmin.h $(RELEASE)

check_objectdir :
	@if [ ! -d "$(TARGET)" ]; then\
		mkdir -p $(TARGET);\
	fi
	@if [ ! -d "$(RELEASE)" ]; then\
		mkdir -p $(RELEASE);\
	fi	
	
$(TARGET)/LinuxcopeAdmin.o: LinuxcopeAdmin.c
	 $(CC) $(CCFLAGS) $(INC_PATH) -c LinuxcopeAdmin.c -o $(TARGET)/LinuxcopeAdmin.o

clean:
	$(RM) -Rf $(TARGET)
	$(RM) -Rf $(RELEASE)
