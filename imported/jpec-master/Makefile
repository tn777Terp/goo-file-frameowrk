####################################################################
#  BOILER PLATE MAKEFILE FOR SRC/INC DIRECTORY FORMAT
####################################################################

.PHONY: all clean help
help: 
	@printf "\t$(BYellow)options: all, help, clean $(NOC)\n\n"

# Parent directory will be passed in as an argument make is called
CWD := $(PWD)

# Main prog name
MAIN_NAME   := main

# project directory	
OBJ_DIR 		?= obj

# Source directory
SRC_DIR = src
INC_DIR = inc

# shell command
CC    := gcc
CXX   := g++
RM    := rm -rf

# Getting file names
sources_c   := $(notdir $(shell find $(SRC_DIR) -name "*.c"  ))
sources_cpp := $(notdir $(shell find $(SRC_DIR) -name "*.cpp"))
sources_h   := $(shell find $(INC_DIR) -name "*.h")

OBJS_ALL    := $(addprefix $(OBJ_DIR)/, $(strip $(sources_cpp:.cpp=.o) $(sources_c:.c=.o)))

CFLAGS     := $(if $(DEBUG),-g -O0 , -O2)
CFLAGS     += $(addprefix -I ,$(sort $(dir $(sources_h))))

CXXFLAGS   = $(CFLAGS)

.PHONY: all clean print
all: $(OBJ_DIR) $(OBJS_ALL)

clean: 
	$(RM) $(OBJ_DIR)

print:
	@echo CWD = $(PWD)
	@echo $(OBJ_DIR)

# Create output directories
$(OBJ_DIR):
	@echo asdfasdf $(OBJ_DIR)
	mkdir -p $@

# Compiling object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

