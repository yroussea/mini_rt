# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 18:31:53 by kiroussa          #+#    #+#              #
#    Updated: 2024/11/17 16:55:17 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= libtocard.so
DEBUG				?= 0

MLX_DIR				= MacroLibX

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror -fPIC -std=c2x
INCLUDES			= -I./include -I$(MLX_DIR)/includes
LDFLAGS				= -shared -pipe

ifeq ($(DEBUG), 1)
	CFLAGS			+= -gdwarf-4 -g3
	LDFLAGS			+= -rdynamic
endif

RM					= rm -rf
MAKE				= make --no-print-directory

SRC_DIR				= src
BUILD_DIR			= build
OBJ_DIR				= $(BUILD_DIR)/obj
OUTPUT				= $(BUILD_DIR)/$(NAME)

SRC					= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ					= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all:				$(OUTPUT)
	
$(NAME):			$(OUTPUT)

$(OUTPUT):			$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 

$(MLX_DIR):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "Cloning MacroLibX..."; \
		git clone https://github.com/seekrs/MacroLibX.git --recursive $(MLX_DIR); \
	fi

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c $(MLX_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean:
	$(RM) $(BUILD_DIR)

re:					fclean all

.PHONY:				all clean fclean re
