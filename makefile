#### #######################################################
# MAKEFILE FOR C/C++ PROJECT
# Forked By Tin Nguyen
# Original Author: swm8023 <swm8023@gmail.com>
# Date:   2014/01/30
#
#### #######################################################
include fonts.mk

.PHONY: all clean help
help: 
	@printf "\t$(BYellow)options: all, help, clean $(NOC)\n\n"

CWD := $(PWD)

# annotation when release version
DEBUG       := y
MAIN_NAME   := main
PROG_NAME   := goo

# project directory	
DEBUG_DIR   := Debug
RELEASE_DIR := Release
BIN_DIR     := $(if $(DEBUG), $(DEBUG_DIR), $(RELEASE_DIR))
OBJ_DIR 		:= $(strip $(BIN_DIR)/src)

# Source directory
SRC_DIR = src
INC_DIR = inc

# shell command
CC    := gcc
CXX   := g++
RM    := rm -rf

# Getting file names
SOURCES_C   := $(notdir $(shell find $(SRC_DIR) -name "*.c"  ))
SOURCES_CPP := $(notdir $(shell find $(SRC_DIR) -name "*.cpp"))
SOURCES_H   := $(shell find $(INC_DIR) -name "*.h")

OBJC       := $(addprefix $(OBJ_DIR)/, $(strip $(SOURCES_C:.c=.o)))
OBJCPP     := $(addprefix $(OBJ_DIR)/, $(strip $(SOURCES_CPP:.c=.o)))
OBJS_CORE  := $(addprefix $(OBJ_DIR)/, $(strip $(SOURCES_CPP:.cpp=.o) $(SOURCES_C:.c=.o)))
OBJS_ALL    = $(shell find $(OBJ_DIR) -name "*.o"  )

# Third party stuff
IMPORT_PARENT_DIR := imported
IMPORT_LIBS_DIRS  := $(wildcard $(IMPORT_PARENT_DIR)/*)
IMPORT_SRC_DIR 	  := $(addsuffix src, $(IMPORT_LIBS_DIRS)/)
IMPORT_INC_DIR 	  := $(addsuffix inc, $(IMPORT_LIBS_DIRS)/)

IMPORT_SOURCES_C  := $(notdir $(shell find $(IMPORT_SRC_DIR) -name "*.c"  ))
IMPORT_OBJS				:= $(addprefix $(OBJ_DIR)/, $(strip $(IMPORT_SOURCES_C:.c=.o)))

# Compiler flags
CFLAGS     := $(if $(DEBUG),-g -O0 , -O2)
CFLAGS     += $(addprefix -I ,$(sort $(dir $(SOURCES_H))))
CFLAGS     += $(addprefix -I ,$(sort $(IMPORT_INC_DIR)))
CFLAGS     += -fgnu89-inline

CXXFLAGS    = $(CFLAGS)
LDFLAGS    := 
LOADLIBES  += #-L/usr/include/mysql
LDLIBS     += #-lpthread -lmysqlclient


# Testing variable value
print:
	@echo $(OBJS_ALL)

# Create output directories
$(OBJ_DIR):
	mkdir -p $@

# Compiling object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Compiling third party project
.PHONY: $(IMPORT_LIBS_DIRS)
$(IMPORT_LIBS_DIRS):
	@printf "$(BPurple)Compiling $@ $(NOC)\n"
	$(MAKE) all -C ./$@ OBJ_DIR=$(CWD)/$(OBJ_DIR)
	@printf '\n'

# Linking object files into executable
$(BIN_DIR)/$(PROG_NAME): $(OBJS_CORE)
	@printf "$(BPurple)Compiling executable$(NOC)\n"
	$(CC) $(OBJS_ALL) -o $@


all: $(OBJ_DIR) $(IMPORT_LIBS_DIRS) $(BIN_DIR)/$(PROG_NAME)
	@printf "\n$(BGreen)Compilation Success!$(NOC)\n\n"

clean: 
	$(RM) $(BIN_DIR)
	$(RM) *.o