# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 09:39:18 by yroussea          #+#    #+#              #
#    Updated: 2024/11/19 17:09:24 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Project variables ###

include config/config.mk

NAME = $(PROJECT_NAME)
PWD := $(shell pwd)
EXTRA_CFLAGS += -DRT_VERSION='"\"$(PROJECT_VERSION)\""'
EXTRA_CFLAGS += -DRT_URL='"\"$(PROJECT_URL)\""'



### Submodules ###

SUBMODULES_DIR = $(PWD)/submodules

# available submodules
SUBMODULES = backend-dummy backend-raytracer frontend-mlx parser-rt shared ui
ifeq ($(DEVELOPMENT_MODE), 1)
SUBMODULES := devreload $(SUBMODULES)
EXTRA_CFLAGS += '-DRT_DEBUG(fmt, ...) = ft_printf(\"%s[%s:%d] \" fmt, RT_DEBUG_PREFIX, __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)'
EXTRA_CFLAGS += '-DRT_DEVMODE=1'
endif

# Collect the output files (submodules/<proj>/lib<proj>.rt.so)
SUBMODULES_OUTPUT =
_ := $(foreach sub,$(SUBMODULES),$(eval SUBMODULES_OUTPUT += $(SUBMODULES_DIR)/$(sub)/lib$(sub)$(LIB_SUFFIX)))
NO_BACKEND_OUTPUT := $(shell echo $(SUBMODULES_OUTPUT) | sed 's/ /\n/g' | grep -v libbackend- | grep -v libfrontend- | sed 's/\n/ /g')

ifeq ($(DEVELOPMENT_MODE), 1)
EXTRA_LDFLAGS := $(NO_BACKEND_OUTPUT)
EXTRA_CFLAGS += '-DRT_DEVRELOAD_SUBMODULES_PATH="\"$(SUBMODULES_DIR)\""'
BACKENDS := $(shell echo $(SUBMODULES) | sed 's/ /\n/g' | grep backend- | tac | sed 's/\n/ /g')
FRONTENDS := $(shell echo $(SUBMODULES) | sed 's/ /\n/g' | grep frontend- | tac | sed 's/\n/ /g')
EXTRA_CFLAGS += '-DRT_DEVRELOAD_BACKENDS=\"$(BACKENDS)\"'
EXTRA_CFLAGS += '-DRT_DEVRELOAD_FRONTENDS=\"$(FRONTENDS)\"'
else
EXTRA_LDFLAGS := $(SUBMODULES_OUTPUT)
endif

MAIN_SUBMODULE = cli
SUBMODULES += $(MAIN_SUBMODULE)
MAIN_SUBMODULE_OUTPUT := $(SUBMODULES_DIR)/$(MAIN_SUBMODULE)/$(MAIN_SUBMODULE)$(EXEC_SUFFIX)

MKDEPS :=
_ := $(foreach sub,$(SUBMODULES),$(eval MKDEPS += $(shell $(MAKE) CACHE_DIR="$(PWD)/$(CACHE_DIR)" -C $(SUBMODULES_DIR)/$(sub) print_MKDEPS)))

# expose every header file to other submodules
EXTRA_CFLAGS += $(SUBMODULES:%=-I$(SUBMODULES_DIR)/%/include)



### Library dependencies (`third-party` directory) ###

DEPS_DIR = $(PWD)/third-party
DEPS := $(shell $(MAKE) -C $(DEPS_DIR) print_DEPS)
DEPS_TARGETS :=
_ := $(foreach dep,$(DEPS),$(eval DEPS_TARGETS += $(DEPS_DIR)/$(shell $(MAKE) -C $(DEPS_DIR) print_$(dep)_TARGET)))
DEPS_DIRS :=
_ := $(foreach dep,$(DEPS),$(eval DEPS_DIRS += $(DEPS_DIR)/$(shell $(MAKE) -C $(DEPS_DIR) print_$(dep)_DIR)))

# expose every header file to submodules
EXTRA_CFLAGS += $(DEPS_DIRS:%=-I%/include) $(DEPS_DIRS:%=-I%/includes)
EXTRA_LDFLAGS += $(DEPS_TARGETS)



### Build daemon config ###

DAEMON_NAME = rebuild-daemon
DAEMON_SCRIPT = $(DAEMON_NAME).sh
DAEMON_TARGET_FILE := $(PWD)/.$(DAEMON_NAME).done
DAEMON_ALIVE_FILE := $(PWD)/.$(DAEMON_NAME).alive
EXTRA_CFLAGS += '-DRT_DEVRELOAD_DAEMON_WATCH_FILE="\"$(DAEMON_TARGET_FILE)\""'



### Make Rules ###

all: $(NAME)

# include the .d files from submodules to check if they should be remade
-include $(MKDEPS)

# invalidation mechanism, delete a .o file if its corresponding .c file has been modified
$(PWD)/$(CACHE_DIR)/%:
	@#echo "[*] Invalidating $@"
	@if [ $(findstring .c, $<) ] || [ $(findstring .s, $<) ]; then \
		rm -rf $@; \
	fi

$(NAME): $(MAIN_SUBMODULE_OUTPUT)
	@echo "[*] Copying $(MAIN_SUBMODULE_OUTPUT) to $(NAME)"
	@ln -fs $(MAIN_SUBMODULE_OUTPUT) $(NAME)

$(SUBMODULES_OUTPUT): | $(DEPS_DIR)
	@$(MAKE) -C $(dir $@) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" CACHE_DIR="$(PWD)/$(CACHE_DIR)"

$(MAIN_SUBMODULE_OUTPUT): $(SUBMODULES_OUTPUT)
	@$(MAKE) -C $(SUBMODULES_DIR)/$(MAIN_SUBMODULE) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" EXTRA_LDFLAGS="$(EXTRA_LDFLAGS)" CACHE_DIR="$(PWD)/$(CACHE_DIR)"
	@touch $(MAIN_SUBMODULE_OUTPUT)

$(DEPS_TARGETS):

$(DEPS_DIR): $(DEPS_TARGETS)
	@echo "[*] Making dependencies..." && sleep 1
	@$(MAKE) -C $(DEPS_DIR) all
	@touch $(DEPS_DIR)

bonus: all

oclean:
	@echo "[!] Removing $(CACHE_DIR)"
	@rm -rf $(CACHE_DIR)

clean: oclean
	@$(MAKE) -C $(DEPS_DIR) clean

fclean:
	@for i in $(SUBMODULES); do \
		$(MAKE) -C $(SUBMODULES_DIR)/$$i CACHE_DIR="$(PWD)/$(CACHE_DIR)" fclean; \
	done
	@echo "[!] Removing $(NAME)"
	@rm -rf $(NAME)
	@$(MAKE) -C $(DEPS_DIR) fclean
	@$(MAKE) oclean

re: fclean all

remake: oclean
	@$(MAKE) all -j

test: all
	@make --no-print-directory -C scenes test

vtest: all
	@make --no-print-directory -C scenes vtest

daemon-stop:
	@echo "[*] Killing daemon..."
	@rm -rf $(DAEMON_ALIVE_FILE)
	@sleep 1

daemon: daemon-stop 
	@echo "[*] Starting daemon..."
	@bash ./$(DAEMON_SCRIPT) $(DAEMON_TARGET_FILE) $(DAEMON_ALIVE_FILE)

valgrind:
ifeq ($(USE_VALGRIND_LOGFILE), 1)
	valgrind $(VALGRIND_FLAGS) --log-file=valgrind.log ./$(NAME) $(VG_ARGS) || true
	@echo "[*] Valgrind log available in valgrind.log"
else
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(VG_ARGS) || true
endif

callgrind:
	valgrind --tool=callgrind ./$(NAME) $(VG_ARGS) || true
	@echo "[*] Callgrind log available in callgrind.log"

flex:
	@nix-shell -p cloc --command "clear; cloc config submodules third-party/libft third-party/tocard-ui ./rebuild-daemon.sh --include-lang=\"C/C++ Header,C,D,make,Nix,Python,Bourne Shell\""

help:
	@printf "Usage: make [target] [VG_ARGS=\"...\"]\n"
	@printf "\n"
	@printf "Targets:\n"
	@printf "    all:\t\tBuild the project (default)\n"
	@printf "    clean:\t\tClean the project\n"
	@printf "    fclean:\t\tClean the project, its submodules, and its dependencies\n"
	@printf "    re:\t\t\tfclean + all\n"
	@printf "    remake:\t\tClean the project and its submodules, then build it (not including dependencies)\n"
	@printf "    test:\t\tRun the parser unit tests (see ./scenes/tester.sh)\n"
	@printf "    daemon:\t\tStart the rebuild daemon\n"
	@printf "    daemon-stop:\tStop the rebuild daemon\n"
	@printf "    flex:\t\tflex.\n"
	@printf "    valgrind:\t\tRun the project with valgrind\n"
	@printf "      VG_ARGS: \t\t- arguments to pass to valgrind\n\n"
	@printf "      > Example:\n"
	@printf "      make valgrind VG_ARGS=\"-b dummy ./scenes/valid/minimal.rt\"\n\n"
	@printf "    help:\t\tDisplay this help message\n"

print_%:
	@echo $($*)

.PHONY: all deps _clean oclean clean fclean re remake daemon-stop daemon valgrind help print_% 
