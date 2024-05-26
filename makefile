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

# annotation when release version
DEBUG       := y
TARGET_PROG := main
PROG_NAME   := goo

# project directory	
DEBUG_DIR   := ./Debug
RELEASE_DIR := ./Release
BIN_DIR     := $(if $(DEBUG), $(DEBUG_DIR), $(RELEASE_DIR))

# shell command
CC    := gcc
CXX   := g++
RM    := rm -rf
MKDIR := mkdir -p
SED   := sed
MV    := mv

# init sources & objects & depends
sources_all := $(shell find . -name "*.c" -o -name "*.cpp" -o -name "*.h")
sources_c   := $(filter %.c, $(sources_all))
sources_cpp := $(filter %.cpp, $(sources_all))
sources_h   := $(filter %.h, $(sources_all))
objs        := $(addprefix $(BIN_DIR)/,$(strip $(sources_cpp:.cpp=.o) $(sources_c:.c=.o)))
deps        := $(addprefix $(BIN_DIR)/,$(strip $(sources_cpp:.cpp=.d) $(sources_c:.c=.d)))

# create directory
$(foreach dirname,$(sort $(dir $(sources_c) $(sources_cpp))),\
  $(shell $(MKDIR) $(BIN_DIR)/$(dirname)))

# complie & link variable
CFLAGS     := $(if $(DEBUG),-g , -O2)
CFLAGS     += $(addprefix -I ,$(sort $(dir $(sources_h))))
CFLAGS     += -fgnu89-inline
CXXFLAGS    = $(CFLAGS)
LDFLAGS    := 
LOADLIBES  += #-L/usr/include/mysql
LDLIBS     += #-lpthread -lmysqlclient

# add vpath
vpath %.h $(sort $(dir $(sources_h)))
vpath %.c $(sort $(dir $(sources_c)))
vpath %.cpp $(sort $(dir $(sources_cpp)))

# generate depend files
# actually generate after object generated, beacasue it only used when next make)
ifneq "$(MAKECMDGOALS)" "clean"
sinclude $(deps)
endif

# make-depend(depend-file,source-file,object-file,cc)
define make-depend
  $(RM) $1;                                     \
  $4 $(CFLAGS) -MM $2 |                         \
  $(SED) 's,\($(notdir $3)\): ,$3: ,' > $1.tmp; \
  $(SED) -e 's/#.*//'                           \
         -e 's/^[^:]*: *//'                     \
         -e 's/ *\\$$//'                        \
         -e '/^$$/ d'                           \
         -e 's/$$/ :/' < $1.tmp >> $1.tmp;      \
  $(MV) $1.tmp $1;
endef

# rules to generate objects file
$(BIN_DIR)/%.o: %.c
	@$(call make-depend,$(patsubst %.o,%.d,$@),$<,$@,$(CC))
	$(CC) $(CFLAGS) -o $@ -c $<

$(BIN_DIR)/%.o: %.cpp
	@$(call make-depend,$(patsubst %.o,%.d,$@),$<,$@,$(CXX))
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# add-target(target,objs,cc)
define add-target
  REAL_TARGET += $(BIN_DIR)/$1
  $(BIN_DIR)/$1: $2
	$3 $(LDFLAGS) $$^ $(LOADLIBES) $(LDLIBS) -o $$@
endef

# call add-target
$(foreach targ,$(TARGET_PROG),$(eval $(call add-target,$(targ),$(objs),$(CXX))))

all: $(REAL_TARGET) $(TARGET_LIBS) $(BIN_DIR)/$(PROG_NAME)

# Rename main file
$(BIN_DIR)/$(PROG_NAME): $(BIN_DIR)/$(TARGET_PROG)
	mv $(BIN_DIR)/$(TARGET_PROG) $@

clean: 
	$(RM) $(BIN_DIR)