
TARGET = x86_64-redhat-linux

CP = cp
RM = rm
CCFLAGS =  -g 
ARFLAGS = -q

RELEASE = ../../release/$(TARGET)

OBJS = \
	$(TARGET)/Tio.o 

pre-build: 	check_objectdir target

target: $(OBJS) $(RELEASE) $(TARGET)
	$(AR) $(ARFLAGS) $(TARGET)/libTio.a $(OBJS)
	$(CP) $(TARGET)/libTio.a $(RELEASE)
	$(CP) Tio.h $(RELEASE)

check_objectdir :
	@if [ ! -d "$(TARGET)" ]; then\
		mkdir -p $(TARGET);\
	fi
	@if [ ! -d "$(RELEASE)" ]; then\
		mkdir -p $(RELEASE);\
	fi	
	
$(TARGET)/Tio.o: Tio.c
	 $(CC) $(CCFLAGS) $(INC_PATH) -c Tio.c -o $(TARGET)/Tio.o

clean:
	$(RM) -Rf $(TARGET)
	$(RM) -Rf $(RELEASE)
