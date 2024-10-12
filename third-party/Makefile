# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 23:49:35 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/12 19:40:43 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEPS = LIBFT MACROLIBX TOCARDUI

LIBFT_DIR = libft
LIBFT_TARGET = $(LIBFT_DIR)/build/output/libft.so
MACROLIBX_DIR = MacroLibX
MACROLIBX_TARGET = $(MACROLIBX_DIR)/libmlx.so
TOCARDUI_DIR = tocard-ui
TOCARDUI_TARGET = $(TOCARDUI_DIR)/build/libtocard.so

SCRIPT = tmux-dispatch.sh

all:
	@bash $(SCRIPT)

update:
	@git submodule update --init --recursive

clean:
	@RULE=clean bash $(SCRIPT)

fclean:
	@RULE=fclean bash $(SCRIPT)

re:
	@RULE=re bash $(SCRIPT)

print_%:
	@echo $($*)

.PHONY: all clean fclean re print_%
