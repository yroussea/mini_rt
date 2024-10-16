# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 00:04:32 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/16 06:50:03 by kiroussa         ###   ########.fr        #
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
	  	rt_devrl_ctor.c \
		rt_devrl_dtor.c \
		rt_devrl_recompile.c

include ../submodule.mk

DEVRELOAD_USE_DLFCN = 0

CFLAGS += -DDLFCN_VERBOSE=1
CFLAGS += '-DRT_DEBUG_PREFIX="[devrl] "'
CFLAGS += -DRT_DEVRELOAD_USE_DLFCN=$(DEVRELOAD_USE_DLFCN)
