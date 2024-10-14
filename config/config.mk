# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 01:41:07 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/14 19:50:16 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME = rt
PROJECT_VERSION = 2.0.2-dev
PROJECT_URL = https://github.com/27network/rt
COMP_MODE = $(PROJECT_NAME)

LIB_SUFFIX = .rt.so
EXEC_SUFFIX = .out

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -gdwarf-4 -fPIC
DFLAGS = -MT $@ -MMD -MP -MF $(MKDEPS_DIR)/$*.tmp.d
LDFLAGS = -lm -lSDL2

MAKE = make --debug=none --no-print-directory -j$(shell nproc)
CACHE_DIR ?= .cache

DEVELOPMENT_MODE ?= 1
