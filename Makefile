SHELL = /bin/sh

CFLAGS := ${CFLAGS}

CC     ?= gcc

INC_FLAGS := -Ilinenoise/
LIBS := -L./linenoise/ -lnoise

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	NPROC := $(shell nproc)
else
	NPROC := $(shell sysctl -n hw.ncpu)
endif

MAKEFLAGS += --output-sync=target
MAKEFLAGS += --no-print-directory

NAME ?= ftdbg

BUILD_DIR ?= ./build
SRC_DIRS ?= ./srcs
INCLUDE_DIR ?= ./includes

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(INCLUDE_DIR) -type d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))

CFLAGS += -Wall -Wextra -Werror
CFLAGS += -std=c99 -pedantic
#CFLAGS += -O3 -march=native
#CFLAGS += -g3
#CFLAGS += -fsanitize=address -v

all:
	@$(MAKE) -C ./linenoise
	@$(MAKE) -j$(NPROC) $(NAME)

$(NAME): $(OBJS)
	@echo Linking $@
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/%.c.o: %.c
	@echo Compiling $@
	@mkdir -p $(dir $@)
	@$(CC) -c  $(CFLAGS) $(INC_FLAGS) $< -o $@

clean:
	@$(MAKE) -C linenoise/ clean
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DIR_BONUS)
	@echo Clean done

fclean:	clean
	@$(MAKE) -C linenoise/ fclean
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@echo Fclean done

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re
