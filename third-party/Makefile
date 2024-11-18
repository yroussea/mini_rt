# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 23:49:35 by kiroussa          #+#    #+#              #
#    Updated: 2024/11/18 01:02:21 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEPS = LIBFT MACROLIBX TOCARDUI LIBTERM

LIBFT_DIR = libft
LIBFT_TARGET = $(LIBFT_DIR)/build/output/libft.so
LIBFT_BRANCH = main
MACROLIBX_DIR = MacroLibX
MACROLIBX_TARGET = $(MACROLIBX_DIR)/libmlx.so
MACROLIBX_BRANCH = master
TOCARDUI_DIR = tocard-ui
TOCARDUI_TARGET = $(TOCARDUI_DIR)/build/libtocard.so
TOCARDUI_BRANCH = main
LIBTERM_DIR = libterm
LIBTERM_TARGET = $(LIBTERM_DIR)/libterm.a
LIBTERM_BRANCH = main

SCRIPT = tmux-dispatch.sh

all:
	@bash $(SCRIPT)

update:
	@git submodule update --init --recursive
	@cd $(LIBFT_DIR); git pull origin $(LIBFT_BRANCH); cd ../
	@cd $(MACROLIBX_DIR); git pull origin $(MACROLIBX_BRANCH); cd ../
	@cd $(TOCARDUI_DIR); git pull origin $(TOCARDUI_BRANCH); cd ../
	# @cd $(LIBTERM_DIR); git pull origin $(LIBTERM_BRANCH); cd ../

clean:
	@RULE=clean bash $(SCRIPT)

fclean:
	@RULE=fclean bash $(SCRIPT)

re:
	@RULE=re bash $(SCRIPT)

print_%:
	@echo $($*)

.PHONY: all clean fclean re print_%
