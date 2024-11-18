# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 01:41:07 by kiroussa          #+#    #+#              #
#    Updated: 2024/11/18 21:15:29 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME = rt
PROJECT_VERSION = 2.1.0-dev
PROJECT_URL = https://github.com/27network/rt
COMP_MODE = $(PROJECT_NAME)

LIB_SUFFIX = .rt.so
EXEC_SUFFIX = .out

CC = clang
CFLAGS = -Wall -Wextra -g -gdwarf-4 -fPIC -fno-plt
# CFLAGS += -Werror
DFLAGS = -MT $@ -MMD -MP -MF $(MKDEPS_DIR)/$*.tmp.d
LDFLAGS = -lm -lSDL2 -fPIC -fno-plt

NASM = nasm
NASMFLAGS = -f elf64

MAKE = make --debug=none --no-print-directory
MAKE_MULTITHREAD ?= 1
ifeq ($(MAKE_MULTITHREAD), 1)
MAKE += -j$(shell nproc)
endif

CACHE_DIR ?= .cache

DEVELOPMENT_MODE ?= 1
USE_VALGRIND_LOGFILE ?= 0
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes --suppressions=third-party/MacroLibX/valgrind.supp -q
