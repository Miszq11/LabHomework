CC= g++
TARGET=a.out
CPPFLAGS=-Wall -pthread
SOURCE_DIR=src
HEADER_DIR=include
SOURCE:=${wildcard ${SOURCE_DIR}/*.cpp}
HEADER:=${wildcard ${HEADER_DIR}/*.h}
OBJECTS:=$(SOURCE:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS) $(CPPFLAGS)
%.o: %.cpp
	$(CC) -o $@ -c $< -I$(HEADER_DIR) $(CPPFLAGS)    
	
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)

