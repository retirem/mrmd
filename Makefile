CXX = g++

CXXFLAGS = -g -Wall

LIBRARIES = -lssl -lcrypto

TARGET = deduplicate

INIT_PATH ?= "test/initial_memdump"
MALICIOUS_PATH ?= "test/malicious_memdump"

RM = rm -rf

all: clean $(TARGET) run

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp $(LIBRARIES)

run: 
	./$(TARGET) $(INIT_PATH) $(MALICIOUS_PATH)

clean:
	$(RM) $(TARGET) $(TARGET).dSYM $(TARGET).bin
