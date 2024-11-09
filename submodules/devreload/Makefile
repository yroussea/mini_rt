# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 00:04:32 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/26 23:45:05 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	backend/rt_devrl_backend_setup.c \
		backend/rt_devrl_load_backend.c \
		dlfcn/ft_dlsym.c \
		dlfcn/ft_dlclose.c \
		dlfcn/ft_dlopen.c \
		dlfcn/ft_mmap.c \
		dlfcn/ft_munmap.c \
		dlfcn/ft_syscall.c \
		frontend/rt_devrl_frontend_setup.c \
	  	frontend/rt_devrl_load_frontend.c \
		rt_devrl_check_reload.c \
	  	rt_devrl_ctor.c \
		rt_devrl_dtor.c

include ../submodule.mk

# Whether to use our own dlfcn implementation or the system's
# 1: ft_dlsym
# 0: dlsym
DEVRELOAD_USE_DLFCN = 0

CFLAGS += -DDLFCN_VERBOSE=1
CFLAGS += '-DRT_DEBUG_PREFIX="[devrl] "'
CFLAGS += -DRT_DEVRELOAD_USE_DLFCN=$(DEVRELOAD_USE_DLFCN)
