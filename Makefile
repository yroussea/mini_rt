# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 09:39:18 by yroussea          #+#    #+#              #
#    Updated: 2024/10/15 22:49:46 by yroussea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SILENT = @

COMPIL = $(CLANG)
ALL_FLAG = -Wall -Werror -Wextra -O3
CC = $(COMPIL) $(ALL_FLAG)

CFLAGS = -g3
CLANG = $(SILENT)clang $(CFLAGS)
GCC = $(SILENT)gcc $(CFLAGS)

DEAD_CODE = -g -ffunction-sections -Wl,--gc-sections -Wl,--print-gc-sections

DEBUGCFLAG = -g -gdwarf-3

SRCS_DIR = src
OBJS_DIR = obj

include sources.mk

SRCS = 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = 	$(addprefix $(OBJS_DIR)/, $(subst .c,.o, $(SRCS_FILES)))


PROJECT = rt
NAME = rt

LIBMLX_DIR = macrolibx
LIBMLX = $(LIBMLX_DIR)/libmlx.so

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/build/output/libft.so

INCLUDE = -I include -I $(LIBMLX_DIR)/includes -I $(LIBFT_DIR)/include

DELET_LINE = $(SILENT) echo -n "\033[2K";
RM = $(SILENT) rm -rf

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
NO_COLOR    = \033[m

bold := $(shell tput bold)
notbold := $(shell tput sgr0)

PRINT = $(SILENT) printf "\r%b"

MSG_CLEANING = "$(COLOUR_RED)$(bold)🧹cleaning $(notbold)$(COLOUR_YELLOW)$(PROJECT)$(NO_COLOR)";
MSG_CLEANED = "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)cleaned $(NO_COLOR)\n";
MSG_COMPILING = "$(COLOUR_YELLOW)$(bold)[💧 Compiling 💧]$(notbold)$(COLOUR_YELLOW) $(^)$(NO_COLOR)";
MSG_READY = "🌱 $(COLOUR_BLUE)$(bold)$(PROJECT) $(COLOUR_GREEN)$(bold)ready$(NO_COLOR)\n";

all: $(NAME)

$(NAME): $(OBJS) | $(OBJS_DIR) $(LIBMLX) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) -L -lft $(LIBFT) $(LIBMLX) -lSDL2 -lm 
	$(DELET_LINE)
	$(PRINT) $(MSG_READY)

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	$(DELET_LINE)
	$(PRINT) $(MSG_COMPILING)
	$(CC) $(INCLUDE)  -c $^ -o $@

$(OBJS_DIR):
	$(SILENT)mkdir -p $@

clean:
	$(PRINT) $(MSG_CLEANING)
	$(RM) $(OBJS_DIR)
	$(DELET_LINE)
	$(PRINT) $(MSG_CLEANED)

fclean: clean
	$(RM) $(NAME)

re: fclean all

--cc:
	$(eval COMPIL = $(CLANG))
	$(eval ALL_FLAG += $(DEBUGCFLAG))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

--gcc:
	$(eval COMPIL = $(GCC))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

--dead_code:
	$(eval ALL_FLAG += $(DEAD_CODE))
	$(eval COMPIL = $(GCC))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

threading:
	$(eval ALL_FLAG += "-D THREAD")
	$(eval CC = $(COMPIL) $(ALL_FLAG))

$(LIBMLX_DIR):
	@git submodule init
	@git submodule update

$(LIBMLX): $(LIBMLX_DIR)
	@make -s -C $(LIBMLX_DIR) -j 


cc: fclean --cc $(NAME)
gcc: fclean --gcc $(NAME)
dead_code: fclean --dead_code $(NAME)

.PHONY: all clean fclean re cc gcc dead_code threading
.SILENT:


