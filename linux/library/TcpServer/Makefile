
CP = cp
CCFLAGS = -g

INC_DIR =   -I../../release \
			-I../../common

ARFLAGS = rs
 
RELEASE = ../../release/$(TARGET)

OBJS = \
	$(TARGET)/TcpServer.o 

pre-build: 	check_objectdir target

target: $(OBJS)
	 $(AR) $(ARFLAGS) $(RELEASE)/libTcpServer.a $(OBJS)
	 $(CP) TcpServer.h $(RELEASE)

check_objectdir :
	@if [ ! -d "$(TARGET)" ]; then\
		mkdir -p $(TARGET);\
	fi
	@if [ ! -d "$(RELEASE)" ]; then\
		mkdir -p $(RELEASE);\
	fi	

$(TARGET)/TcpServer.o: TcpServer.cpp
	 $(CC) $(CCFLAGS) -c TcpServer.cpp -o $(TARGET)/TcpServer.o
				 	
clean:
	rm -Rf $(TARGET)
