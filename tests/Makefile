LINKER		= gcc
COMPILER	= $(LINKER) -c
FLAGS_C		= -Wall -Wextra -Werror

REMOVE		= rm
REMOVE_FORCE	= $(REMOVE) -rf

ifdef GDB
COMPILER	+= -g3
endif

# DIRECTORIES
DIR_ROOT	= ..
DIR_SRC		= $(DIR_ROOT)/src
DIR_TEST	= $(DIR_ROOT)/tests
DIR_INCL	= $(DIR_ROOT)/lib
DIR_UNIT	= $(DIR_ROOT)/tests/Unity
# UNIT DIRECTORIES
DIR_SRC_UNIT	= $(DIR_UNIT)/src
DIR_FIXT_UNIT	= $(DIR_UNIT)/extras/fixture/src
DIR_MEM_UNIT	= $(DIR_UNIT)/extras/memory/src
# FILES
PATH_INCL	= -I. -I$(DIR_INCL) -I$(DIR_SRC_UNIT) -I$(DIR_FIXT_UNIT) -I$(DIR_MEM_UNIT) 
FILE_HEADER	= tests.h
FILE_HEADER_UNIT	= $(DIR_SRC_UNIT)/unity.h
UNIT_FIXT_HEAD	= $(DIR_FIXT_UNIT)/unity_fixture.h
FILE_SRC	= $(filter-out %main.c,  $(wildcard $(DIR_SRC)/*c))
FILE_SRC	+= $(wildcard $(DIR_TEST)/tests/*c)
# FILE_SRC	+= $(subst main.c, tests.c, $(FILE_SRC))
FILE_OBJ	= $(FILE_SRC:%.c=%.o)

FILE_SRC_UNIT	= $(DIR_SRC_UNIT)/unity.c 
FILE_FIXT_UNIT	= $(DIR_FIXT_UNIT)/unity_fixture.c 
 
NAME		= tester 
# LIBFT		= ../libraries/libft/libft.a

all: $(NAME)

$(NAME): $(FILE_OBJ) $(FILE_HEADER)
	$(LINKER) $(FLAGS_C) $(FILE_SRC_UNIT) $(FILE_FIXT_UNIT) $(FILE_OBJ) $(PATH_INCL) -o $@

%.o: %.c $(FILE_HEADER)
	$(COMPILER) $(PATH_INCL) $< -o $@

clean:
	$(REMOVE_FORCE) $(FILE_OBJ)

fclean: clean
	$(REMOVE_FORCE) $(NAME)

re: fclean all

debug:
	gdb -tui -q $(NAME)

test: all clean
	./$(NAME)

.PHONY: all clean fclean re debug test
