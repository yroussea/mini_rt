# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 09:39:18 by yroussea          #+#    #+#              #
#    Updated: 2024/08/28 08:08:02 by yroussea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SILENT = @

COMPIL = $(CLANG)
ALL_FLAG = -Wall -Werror -Wextra
CC = $(COMPIL) $(ALL_FLAG)

CFLAGS = -flto -g3 -fopenmp
CLANG = $(SILENT)clang $(CFLAGS)
GCC = $(SILENT)gcc $(CFLAGS)

DEAD_CODE = -g -ffunction-sections -Wl,--gc-sections -Wl,--print-gc-sections

DEBUGCFLAG = -g -gdwarf-3

SRCS_DIR = scrs
OBJS_DIR = obj

include sources.mk

SRCS = 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = 	$(addprefix $(OBJS_DIR)/, $(subst .c,.o, $(SRCS_FILES)))

INCLUDE = -I include -I macrolibx/includes

PROJECT = rt
NAME = rt

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

$(NAME): $(OBJS) | $(OBJS_DIR)
	git submodule init
	git submodule update
	@make -s -C macrolibx
	$(CC) $(OBJS) -o $(NAME) -L -lft ./macrolibx/libmlx.so -lSDL2 -lm 
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


cc: fclean --cc $(NAME)
gcc: fclean --gcc $(NAME)
dead_code: fclean --dead_code $(NAME)

.PHONY: all clean fclean re cc gcc dead_code threading
.SILENT:


