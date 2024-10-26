# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    submodule.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 01:53:08 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/26 01:57:50 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SRC
SRC :=
endif

PWD := $(shell pwd)

ifndef NAME
NAME := $(shell basename $(PWD))
endif

ifdef CACHE_DIR
PROJ_CACHE_DIR := $(CACHE_DIR)/$(NAME)
INDEPENDENT_CACHE_DIR = 0
else
PROJ_CACHE_DIR := $(PWD)/$(CACHE_DIR)
INDEPENDENT_CACHE_DIR = 1
endif

include ../../config/config.mk

ifdef EXTRA_CFLAGS
CFLAGS += $(EXTRA_CFLAGS)
else
CFLAGS += $(shell $(MAKE) -C ../../ print_EXTRA_CFLAGS) 
endif

ifdef EXTRA_LDFLAGS
LDFLAGS += $(EXTRA_LDFLAGS)
endif

IS_EXEC ?= 0

ifeq ($(IS_EXEC), 1)
TARGET_NAME = $(NAME)$(EXEC_SUFFIX)
LINK_COMMAND = $(CC) -o $(TARGET_NAME) $(OBJ) $(LDFLAGS)
else
TARGET_NAME = lib$(NAME)$(LIB_SUFFIX)
LINK_COMMAND = $(CC) -shared -o $(TARGET_NAME) $(OBJ) $(LDFLAGS)
endif

DEPS ?=

SRC_DIR = src
INCLUDE_DIR = include

CFLAGS += -I$(PWD)/$(INCLUDE_DIR)

OBJ_DIR = $(PROJ_CACHE_DIR)/obj
MKDEPS_DIR = $(PROJ_CACHE_DIR)/makedeps
SELF_DEP = $(MKDEPS_DIR)/_module.d

OBJ 	:= $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRC)))
MKDEPS	:= $(patsubst %.c,%.d,$(patsubst %.s,,$(SRC)))
SRC 	:= $(addprefix $(SRC_DIR)/,$(SRC))
OBJ 	:= $(addprefix $(OBJ_DIR)/,$(OBJ))
MKDEPS	:= $(addprefix $(MKDEPS_DIR)/,$(MKDEPS))
MKDEPS	+= $(SELF_DEP)

all: $(TARGET_NAME)

-include $(MKDEPS)

$(TARGET_NAME): $(OBJ) $(SELF_DEP)
	@echo "<$(NAME)> Linking $(NAME)"
	@$(LINK_COMMAND)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)	
	@mkdir -p $(dir $(MKDEPS_DIR)/$*)
	@echo "<$(NAME)> Compiling $<"
	@$(CC) $(CFLAGS) $(DFLAGS) -c $(PWD)/$< -o $@
	@echo "$(PWD)/$<:" >> $(MKDEPS_DIR)/$*.tmp.d
	@# dumb fixes, see https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
	@mv -f $(MKDEPS_DIR)/$*.tmp.d $(MKDEPS_DIR)/$*.d
	@touch $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	@echo "<$(NAME)> Assembling $<"
	@$(NASM) $(NASMFLAGS) -o $@ $<
	@echo "$(PWD)/$<:" >> $(MKDEPS_DIR)/$*.tmp.d
	@# dumb fixes, see https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
	@mv -f $(MKDEPS_DIR)/$*.tmp.d $(MKDEPS_DIR)/$*.d
	@touch $@

$(SELF_DEP):
	@mkdir -p $(dir $(SELF_DEP))
	@echo "$(PWD)/$(TARGET_NAME): $(OBJ)" > $(SELF_DEP)

clean:
	@if [ $(INDEPENDENT_CACHE_DIR) -eq 1 ]; then \
		echo "<$(NAME)> Removing $(PROJ_CACHE_DIR)"; \
		rm -rf $(PROJ_CACHE_DIR); \
	fi

fclean: clean
	@echo "<$(NAME)> Removing $(TARGET_NAME)"
	@rm -rf $(TARGET_NAME)

re: fclean all

print_%:
	@echo $($*)

.PHONY: all clean fclean re print_%
