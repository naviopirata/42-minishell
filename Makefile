LINKER				= gcc
#LINKER				= cc
#LINKER				= clang
COMPILER			= $(LINKER) -c

REMOVE				= rm
REMOVE_FORCE		= $(REMOVE) -rf
MAKE_DIR			= mkdir -p
DEBUG				= gdb -q -tui
MEMCHECK			= valgrind

FLAG_C				= -g -Wall -Wextra -Werror
FLAG_LEAK			= --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp
FLAG_LEAK			+= -s

LIBFT				= $(PATH_LIBFT)/libft.a
INCLUDES			= -I $(PATH_INCLUDES) -I $(PATH_LIBFT)

PATH_TESTS			= tests
PATH_LIBFT			= lib
PATH_OBJECTS		= obj
PATH_INCLUDES		= incl
VPATH				= $(shell find src type -depth)

NAME				= minishell
FILE_HEADER			= $(PATH_INCLUDES)/minishell.h
FILE_OBJECTS		=	$(patsubst %.c,$(PATH_OBJECTS)/%.o, $(FILE_SOURCES))

FILE_SOURCES		= redirect.c minishell.c cmd_run.c

all: $(NAME)

$(NAME): $(PATH_OBJECTS) $(FILE_OBJECTS) $(LIBFT) $(FILE_HEADER)
	$(LINKER) $(FILE_OBJECTS) $(LIBFT) $(FLAG_C) -o $@ $(INCLUDES) -lreadline -o $@

$(LIBFT):
	@$(MAKE) -C $(PATH_LIBFT) all

$(PATH_OBJECTS):
	$(MAKE_DIR) $(PATH_OBJECTS)

$(PATH_OBJECTS)/%.o: %.c 
	$(COMPILER) $< -c $(FLAG_C) $(INCLUDES) -o $@

clean:
	$(REMOVE_FORCE) $(PATH_OBJECTS)
	@$(MAKE) -C $(PATH_LIBFT) clean

fclean: clean
	$(REMOVE_FORCE) $(NAME)
	@$(MAKE) -C $(PATH_LIBFT) fclean

re: fclean all

run: all
	./$(NAME)

debug: all
	$(DEBUG) ./$(NAME)

leak:
	$(MEMCHECK) $(FLAG_LEAK) ./$(NAME)

test: all
	$(MAKE) -C $(PATH_TESTS) all
	mv tester .

.PHONY: all fclean clean re run leak test debug
