
TARGET = x86_64-redhat-linux

CP = cp
RM = rm
CCFLAGS =  -g 
ARFLAGS = -q

RELEASE = ../../release/$(TARGET)

OBJS = \
	$(TARGET)/Linuxcope.o 

pre-build: 	check_objectdir target

target: $(OBJS) $(RELEASE) $(TARGET)
	$(AR) $(ARFLAGS) $(TARGET)/libLinuxcope.a $(OBJS)
	$(CP) $(TARGET)/libLinuxcope.a $(RELEASE)
	$(CP) Linuxcope.h $(RELEASE)

check_objectdir :
	@if [ ! -d "$(TARGET)" ]; then\
		mkdir -p $(TARGET);\
	fi
	@if [ ! -d "$(RELEASE)" ]; then\
		mkdir -p $(RELEASE);\
	fi	
	
$(TARGET)/Linuxcope.o: Linuxcope.c
	 $(CC) $(CCFLAGS) $(INC_PATH) -c Linuxcope.c -o $(TARGET)/Linuxcope.o

clean:
	$(RM) -Rf $(TARGET)
	$(RM) -Rf $(RELEASE)
