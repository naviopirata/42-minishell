LINKER			= gcc
COMPILER		= $(LINKER) -c

REMOVE			= rm
REMOVE_FORCE		= $(REMOVE) -rf
MAKE_DIR		= mkdir -p
DEBUG			= gdb -q -tui
MEMCHECK		= valgrind

FLAG_C			= -g -Wall -Wextra -Werror
FLAG_LEAK		= --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp
FLAG_LEAK		+= -s

PATH_INCLUDES		= incl
PATH_SOURCES		= src
PATH_OBJECTS		= obj
PATH_LIBRARIES		= lib
PATH_TESTS		= tests
PATH_LIBFT		= $(PATH_LIBRARIES)

LIBFT			= $(PATH_LIBFT)/libft.a
INCLUDES		= -I$(PATH_INCLUDES) -I$(PATH_LIBFT)

NAME			= minishell
SOURCE			= $(addprefix $(PATH_SOURCES)/, $(FILE_SOURCES))
FILE_HEADER		= $(PATH_INCLUDES)/minishell.h
FILE_OBJECTS		= $(SOURCE:$(PATH_SOURCES)/%.c=$(PATH_OBJECTS)/%.o)

FILE_SOURCES		= minishell.c
FILE_SOURCES		+= signals_init.c abstree_init.c

all: $(NAME)

$(NAME): $(LIBFT) $(PATH_OBJECTS) $(FILE_OBJECTS) $(FILE_HEADER)
	$(LINKER) $(FLAG_C) $(FILE_OBJECTS) $(LIBFT) -lreadline -o $@

$(LIBFT):
	@$(MAKE) -C $(PATH_LIBFT) all

$(PATH_OBJECTS):
	$(MAKE_DIR) $(PATH_OBJECTS)

$(PATH_OBJECTS)/%.o: $(PATH_SOURCES)/%.c $(FILE_HEADER)
	$(COMPILER) $(FLAG_C) $(INCLUDES) $< -o $@

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
