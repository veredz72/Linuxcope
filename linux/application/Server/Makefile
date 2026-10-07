
TARGET = x86_64-redhat-linux

OBJS 		=	$(TARGET)/Main.o\
				$(TARGET)/Catalog.o\
				$(TARGET)/BaseProtocol.o\
				$(TARGET)/TcpProtocol.o\
				$(TARGET)/RecordControlRequest.o\
				$(TARGET)/ReadEventsRequest.o

AR = ar

INCLUDES 	= -I../../library/TcpServer
			  
CCFLAGS		= -g $(INCLUDES)

ARFLAGS		= rs
export TARGET
export AR
export CC
export ARFLAGS
export CCFLAGS

RELEASE =	../../release/$(TARGET)
LIBS =		-lpthread -lstdc++\
			-L../../release/$(TARGET) -lTcpServer\
			-L../../release/$(TARGET) -lLinuxcopeAdmin


pre-build: 	check_objectdir target

target: $(OBJS) 
	make -C ../../library/TcpServer 
	make -C ../../library/LinuxcopeAdmin 
	$(CC) $(CCFLAGS) $(OBJS) -o Target.out $(LIBS) 

check_objectdir :
	@if [ ! -d "$(TARGET)" ]; then\
		mkdir -p $(TARGET);\
	fi
				
$(TARGET)/Main.o: Main.cpp 
	$(CC) $(INCLUDES) $(CCFLAGS) -c Main.cpp -o $(TARGET)/Main.o

$(TARGET)/Catalog.o: Catalog.cpp 
	$(CC) $(INCLUDES) $(CCFLAGS) -c Catalog.cpp -o $(TARGET)/Catalog.o

$(TARGET)/BaseProtocol.o: BaseProtocol.cpp 
	$(CC) $(INCLUDES) $(CCFLAGS) -c BaseProtocol.cpp -o $(TARGET)/BaseProtocol.o

$(TARGET)/TcpProtocol.o: TcpProtocol.cpp 
	$(CC) $(INCLUDES) $(CCFLAGS) -c TcpProtocol.cpp -o $(TARGET)/TcpProtocol.o

$(TARGET)/RecordControlRequest.o: RecordControlRequest.cpp 
	$(CC) $(INCLUDES) $(CCFLAGS) -c RecordControlRequest.cpp -o $(TARGET)/RecordControlRequest.o

$(TARGET)/ReadEventsRequest.o: ReadEventsRequest.cpp 
	$(CC) $(INCLUDES) $(CCFLAGS) -c ReadEventsRequest.cpp -o $(TARGET)/ReadEventsRequest.o

clean: 
	make -C ../../library/TcpServer clean 
	make -C ../../library/LinuxcopeAdmin clean 
	rm -Rf $(TARGET)
