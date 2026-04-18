# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Libraries (IMPORTANT for Windows sockets)
LIBS = -lws2_32

# Output files
SERVER = server.exe
CLIENT = client.exe

# Source files
SERVER_SRC = server.cpp
CLIENT_SRC = client.cpp

# Default target
all: $(SERVER) $(CLIENT)

# Build server
$(SERVER): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SERVER) $(SERVER_SRC) $(LIBS)

# Build client
$(CLIENT): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $(CLIENT) $(CLIENT_SRC) $(LIBS)

# Clean build files
clean:
	del /Q *.exe 2>nul || rm -f *.exe

# Run server
run_server:
	./$(SERVER)

# Run client
run_client:
	./$(CLIENT)