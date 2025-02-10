CXX = g++

CXXFLAGS = -g -Wall -I/usr/include/openssl -L/usr/lib/x86_64-linux-gnu -lssl -lcrypto

TARGET = deduplicate

INIT_PATH = "./README.md"
MALICIOUS_PATH = "./ASDASD "

RM = rm -rf

all: clean $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

run: 
	./$(TARGET) $(INIT_PATH) $(MALICIOUS_PATH)

clean:
	$(RM) $(TARGET) $(TARGET).dSYM
