NAME =	pipex

CC = cc
CFLAGS =	#-Wall -Wextra -Werror
RM =		rm -rf

SRC_DIR =	./src/
OBJ_DIR =	./obj/
INC_DIR =	./includes/
PRINTF_DIR	=	./printf/

SRC_LIST =		main.c \
				utils.c \
				ft_strlcpy.c \
				ft_split.c

OBJ_LIST =		$(SRC:%.c=%.o)

HEADERS_LIST =	pipex.h \
				error.h \

SRC =		$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ =		$(addprefix $(OBJ_DIR), $(notdir $(OBJ_LIST)))
HEADERS =	$(addprefix $(INC_DIR), $(HEADERS_LIST))
PRINTF	=	$(addprefix $(PRINTF_DIR), libftprintf.a)

.PHONY: all clean fclean re

all:	$(PRINTF) $(NAME)

$(PRINTF):
		make -C ./printf/

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(PRINTF) -o $(NAME)

$(OBJ_DIR):
		mkdir $(OBJ_DIR)
	
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ_DIR)

fclean:	clean
		$(RM) $(NAME)

re:		fclean $(OBJ_DIR) all