# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 09:39:18 by yroussea          #+#    #+#              #
#    Updated: 2024/10/12 04:31:14 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Project variables ###

include config.mk

NAME = $(PROJECT_NAME)
PWD := $(shell pwd)



### Submodules ###

SUBMODULES_DIR = $(PWD)/submodules

SUBMODULES = parser
# ifeq ($(DEVELOPMENT_MODE), 1)
# SUBMODULES += dev-reload
# endif

# Collect the output files (submodules/<proj>/lib<proj>.rt.so)
SUBMODULES_OUTPUT =
_ := $(foreach sub,$(SUBMODULES),$(eval SUBMODULES_OUTPUT += $(SUBMODULES_DIR)/$(sub)/lib$(sub)$(LIB_SUFFIX)))
EXTRA_LDFLAGS := $(SUBMODULES_OUTPUT)

MAIN_SUBMODULE = cli
SUBMODULES += $(MAIN_SUBMODULE)
MAIN_SUBMODULE_OUTPUT := $(SUBMODULES_DIR)/$(MAIN_SUBMODULE)/$(MAIN_SUBMODULE)$(EXEC_SUFFIX)

MKDEPS :=
_ := $(foreach sub,$(SUBMODULES),$(eval MKDEPS += $(shell $(MAKE) CACHE_DIR="$(PWD)/$(CACHE_DIR)" -C $(SUBMODULES_DIR)/$(sub) print_MKDEPS)))

EXTRA_CFLAGS := $(SUBMODULES:%=-I$(SUBMODULES_DIR)/%/include)


### Library dependencies (`third-party` directory) ###

DEPS_DIR = $(PWD)/third-party
DEPS := $(shell $(MAKE) -C $(DEPS_DIR) print_DEPS)
DEPS_TARGETS :=
_ := $(foreach dep,$(DEPS),$(eval DEPS_TARGETS += $(DEPS_DIR)/$(shell $(MAKE) -C $(DEPS_DIR) print_$(dep)_TARGET)))
DEPS_DIRS :=
_ := $(foreach dep,$(DEPS),$(eval DEPS_DIRS += $(DEPS_DIR)/$(shell $(MAKE) -C $(DEPS_DIR) print_$(dep)_DIR)))

EXTRA_CFLAGS += $(DEPS_DIRS:%=-I%/include) $(DEPS_DIRS:%=-I%/includes)
EXTRA_LDFLAGS += $(DEPS_TARGETS)


### Make Rules ###

all: $(NAME)

-include $(MKDEPS)

# invalidation mechanism
$(PWD)/$(CACHE_DIR)/%:
	@if [ $(findstring .c, $<) ]; then \
		rm -rf $@; \
	fi

$(NAME): $(MAIN_SUBMODULE_OUTPUT)
	@echo "[*] Copying $(MAIN_SUBMODULE_OUTPUT) to $(NAME)"
	@ln -fs $(MAIN_SUBMODULE_OUTPUT) $(NAME)

$(SUBMODULES_OUTPUT): | $(DEPS_DIR)
	@$(MAKE) -C $(dir $@) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" CACHE_DIR="$(PWD)/$(CACHE_DIR)"

$(MAIN_SUBMODULE_OUTPUT): $(SUBMODULES_OUTPUT)
	@echo "[*] Making $(MAIN_SUBMODULE)"
	@$(MAKE) -C $(SUBMODULES_DIR)/$(MAIN_SUBMODULE) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" EXTRA_LDFLAGS="$(EXTRA_LDFLAGS)" CACHE_DIR="$(PWD)/$(CACHE_DIR)"

$(DEPS_TARGETS):

$(DEPS_DIR): $(DEPS_TARGETS)
	@echo "[*] Making dependencies..." && sleep 1
	@$(MAKE) -C $(DEPS_DIR) all
	@touch $(DEPS_DIR)

deps:
	@$(MAKE) -C $(DEPS_DIR) $(DEPS:%=print_%_DIR)

_clean:
	@:

clean: _clean
	@$(MAKE) -C $(DEPS_DIR) clean
	@for i in $(SUBMODULES); do \
		$(MAKE) -C $(SUBMODULES_DIR)/$$i CACHE_DIR="$(PWD)/$(CACHE_DIR)" clean; \
	done

fclean: _clean
	$(MAKE) -C $(DEPS_DIR) fclean
	@for i in $(SUBMODULES); do \
		$(MAKE) -C $(SUBMODULES_DIR)/$$i CACHE_DIR="$(PWD)/$(CACHE_DIR)" fclean; \
	done
	@echo "[!] Removing $(CACHE_DIR)"
	@rm -rf $(CACHE_DIR)
	@rm -rf $(NAME)

re: fclean all

print_%:
	@echo $($*)

.PHONY: all deps _clean clean fclean re print_% 
