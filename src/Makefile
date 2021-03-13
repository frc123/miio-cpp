rapidjson_header = rapidjson/document.h rapidjson/reader.h rapidjson/allocators.h \
 rapidjson/rapidjson.h rapidjson/stream.h rapidjson/encodings.h \
 rapidjson/encodedstream.h rapidjson/memorystream.h \
 rapidjson/internal/clzll.h rapidjson/internal/../rapidjson.h \
 rapidjson/internal/meta.h rapidjson/internal/stack.h \
 rapidjson/internal/../allocators.h rapidjson/internal/swap.h \
 rapidjson/internal/strtod.h rapidjson/internal/ieee754.h \
 rapidjson/internal/biginteger.h rapidjson/internal/diyfp.h \
 rapidjson/internal/clzll.h rapidjson/internal/pow10.h \
 rapidjson/error/error.h rapidjson/error/../rapidjson.h \
 rapidjson/internal/strfunc.h rapidjson/internal/../stream.h \
 rapidjson/internal/../rapidjson.h rapidjson/prettywriter.h \
 rapidjson/writer.h rapidjson/internal/dtoa.h rapidjson/internal/itoa.h \
 rapidjson/internal/itoa.h rapidjson/stringbuffer.h
EXE = miio-cpp
CFLAGS = -Wall -g
C++FLAGS = -std=c++11 -Wall -g

CC = gcc
CC++ = g++
# IMPORTANT: If your machine is Big Endian, please remove the following "#"
# CFLAGS += -DBIGENDIAN
# C++FLAGS += -DBIGENDIAN

objects = main.o mi_home_aircondition.o mi_home_device.o socket_class.o \
 log_process.o md5.o aes.o type_tools.o
# -ldl
$(EXE): $(objects)
	$(CC++) -o $(EXE) $(objects) 

aes.o: aes.c aes.h
	$(CC) -c $(CFLAGS) $< -o $@
log_process.o: log_process.cpp log_process.h stdafx.h
	$(CC++) -c $(C++FLAGS) $< -o $@
main.o: main.cpp stdafx.h log_process.h socket_class.h \
 mi_home_aircondition.h mi_home_device.h md5.h aes.hpp aes.h \
 $(rapidjson_header)
	$(CC++) -c $(C++FLAGS) $< -o $@
md5.o: md5.cpp md5.h
	$(CC++) -c $(C++FLAGS) $< -o $@
mi_home_aircondition.o: mi_home_aircondition.cpp mi_home_aircondition.h \
 stdafx.h mi_home_device.h socket_class.h md5.h aes.hpp aes.h \
 $(rapidjson_header)
	$(CC++) -c $(C++FLAGS) $< -o $@
mi_home_device.o: mi_home_device.cpp mi_home_device.h stdafx.h \
 socket_class.h md5.h aes.hpp aes.h $(rapidjson_header) type_tools.h
	$(CC++) -c $(C++FLAGS) $< -o $@
socket_class.o: socket_class.cpp socket_class.h stdafx.h log_process.h
	$(CC++) -c $(C++FLAGS) $< -o $@
type_tools.o: type_tools.cpp type_tools.h stdafx.h
	$(CC++) -c $(C++FLAGS) $< -o $@

.PHONY : cleanobj clean
cleanobj :
	-rm $(objects)
clean :
	-rm $(EXE) $(objects)
