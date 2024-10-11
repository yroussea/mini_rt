# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 23:49:35 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/11 19:43:09 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEPS = LIBFT MACROLIBX TOCARDUI

LIBFT_DIR = libft
LIBFT_TARGET = build/outputs/libft.so
MACROLIBX_DIR = MacroLibX
MACROLIBX_TARGET = libmlx.so
TOCARDUI_DIR = tocard-ui
TOCARDUI_TARGET = build/libtocard.so

BUILD_DEPS := $(addprefix build_, $(DEPS))
CLEAN_DEPS := $(addprefix clean_, $(DEPS))
FCLEAN_DEPS := $(addprefix fclean_, $(DEPS))

MAKE := make --no-print-directory -j$(shell nproc) CC="$(CC)" MLX_DIR="../$(MACROLIBX_DIR)"

all: $(BUILD_DEPS)

$(BUILD_DEPS):
	@printf ">>> Building %s\n" $($(@:build_%=%)_DIR)
	@$(MAKE) -C $($(@:build_%=%)_DIR)

clean: $(CLEAN_DEPS)

fclean: $(FCLEAN_DEPS)

$(CLEAN_DEPS):
	@printf ">>> Cleaning %s\n" $($(@:build_%=%)_DIR)
	@$(MAKE) -C $($(@:clean_%=%)_DIR) clean

$(FCLEAN_DEPS):
	@printf ">>> Full Cleaning %s\n" $($(@:build_%=%)_DIR)
	@$(MAKE) -C $($(@:fclean_%=%)_DIR) fclean

print_%:
	@echo $($*)

.PHONY: all print_%
