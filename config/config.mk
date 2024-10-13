# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 01:41:07 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/13 04:13:17 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME = miniRT
PROJECT_VERSION = 2.0.1-dev

LIB_SUFFIX = .rt.so
EXEC_SUFFIX = .out

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -gdwarf-4
DFLAGS = -MT $@ -MMD -MP -MF $(MKDEPS_DIR)/$*.tmp.d
LDFLAGS = -lm -lSDL2

MAKE = make --debug=none --no-print-directory
CACHE_DIR ?= .cache

DEVELOPMENT_MODE ?= 1
