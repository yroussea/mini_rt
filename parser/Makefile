# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 13:34:17 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/10 15:05:40 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBNAME			= parser.rt
NAME			= $(LIBNAME).so

SRC_DIR			= src
INCLUDE_DIR		= include
OBJ_DIR			= obj

CC				= clang
CFLAGS			= -Wall -Wextra -Werror -O3 -g -gdwarf-3
CFLAGS			+= -I./$(INCLUDE_DIR)
LDFLAGS			= -shared -lm

SOURCES_FILE	= sources.mk

-include $(SOURCES_FILE)

OBJ				:= $(SRC:.c=.o)
SRC				:= $(addprefix $(SRC_DIR)/,$(SRCS))
OBJ				:= $(addprefix $(OBJ_DIR)/,$(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\033[2KLinking $<\r"
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)
	@printf "\033[2KDone.\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[2KCompiling $<\r"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ) 

fclean: clean
	@rm -rf $(NAME)

re: fclean all

print_%:
	@echo "$($*)"

.PHONY: all clean fclean re print_%
