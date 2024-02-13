# Compiler settings
CC = clang++
LD = clang++
CPPFLAGS = -std=c++17 -I/opt/iot/include -D__DEBUG__=1
LDFLAGS = -L/opt/iot/lib -liot -lpthread

# Application names
CLIENT_APP = client_app
SERVER_APP = server_app

# Directories
BUILD_DIR = build
SRC_DIR = src

# Source and header files
CLIENT_SOURCES = $(SRC_DIR)/main.cpp
SERVER_SOURCES = $(SRC_DIR)/receive.cpp
HEADERS = /opt/iot/include/util.hpp /opt/iot/include/iot/socket.hpp

# Object files
CLIENT_OBJECTS = $(CLIENT_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
SERVER_OBJECTS = $(SERVER_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(BUILD_DIR)/$(CLIENT_APP) $(BUILD_DIR)/$(SERVER_APP)

# Linking the executables
$(BUILD_DIR)/$(CLIENT_APP): $(CLIENT_OBJECTS)
	@echo "Linking $@"
	@$(LD) $(CLIENT_OBJECTS) $(LDFLAGS) -o $@
	@echo "Linking complete"

$(BUILD_DIR)/$(SERVER_APP): $(SERVER_OBJECTS)
	@echo "Linking $@"
	@$(LD) $(SERVER_OBJECTS) $(LDFLAGS) -o $@
	@echo "Linking complete"

# Compiling source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(BUILD_DIR)
	@echo "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

# Create build directory
$(BUILD_DIR):
	@mkdir -p $@

# Run the client application
run-client: $(BUILD_DIR)/$(CLIENT_APP)
	@./$<

# Run the server application
run-server: $(BUILD_DIR)/$(SERVER_APP)
	@./$<

# Clean up
clean:
	@echo "Cleaning up"
	@rm -rf $(BUILD_DIR)

# Mark targets as not generating files
.PHONY: all run-client run-server clean
