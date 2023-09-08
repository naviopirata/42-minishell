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
PATH_BUILTINS		= $(PATH_SOURCES)/builtins
PATH_EXECUTOR		= $(PATH_SOURCES)/executor
PATH_EXPANDER		= $(PATH_SOURCES)/expander
PATH_LAXER			= $(PATH_SOURCES)/laxer
PATH_LINKED_LIST	= $(PATH_SOURCES)/linked_list
PATH_PARSER			= $(PATH_SOURCES)/parser
PATH_REDIRECTIONS	= $(PATH_SOURCES)/redirections
PATH_SIGNALS		= $(PATH_SOURCES)/signals
PATH_UTILS			= $(PATH_SOURCES)/utils
PATH_OBJECTS		= obj
PATH_LIBRARIES		= lib
PATH_TESTS		= tests
PATH_LIBFT		= $(PATH_LIBRARIES)

LIBFT			= $(PATH_LIBFT)/libft.a
INCLUDES		= -I$(PATH_INCLUDES) -I$(PATH_LIBFT)

NAME			= minishell
SOURCE			= $(addprefix $(PATH_SOURCES)/, $(FILE_SOURCES))
SOURCE			+= $(addprefix $(PATH_BUILTINS)/, $(FILE_BUILTINS))
SOURCE			+= $(addprefix $(PATH_EXECUTOR)/, $(FILE_EXECUTOR))
SOURCE			+= $(addprefix $(PATH_LEXER)/, $(FILE_LEXER))
SOURCE			+= $(addprefix $(PATH_LINKED_LIST)/, $(FILE_LINKED_LIST))
SOURCE			+= $(addprefix $(PATH_PARSER)/, $(FILE_PARSER))
SOURCE			+= $(addprefix $(PATH_REDIRECTIONS)/, $(FILE_REDIRECTIONS))
SOURCE			+= $(addprefix $(PATH_SIGNALS)/, $(FILE_SIGNALS))
SOURCE			+= $(addprefix $(PATH_UTILS)/, $(FILE_UTILS))

FILE_HEADER		= $(PATH_INCLUDES)/minishell.h
FILE_OBJECTS		= $(SOURCE:$(PATH_SOURCES)/%.c=$(PATH_OBJECTS)/%.o)

FILE_SOURCES		= minishell.c cmd_run.c
FILE_BUILTINS		=
FILE_EXECUTOR		=
FILE_LEXER			=
FILE_LINKED_LIST	=
FILE_PARSER			=
FILE_REDIRECTIONS	=
FILE_SIGNALS		=
FILE_UTILS			=

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
