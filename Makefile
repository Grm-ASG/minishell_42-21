# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 19:31:28 by imedgar           #+#    #+#              #
#    Updated: 2020/11/18 22:12:11 by imedgar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#			The main programm
NAME			=	minishell

#			Source files
SRC				=	main.c

SRC_ERR			=	ft_error.c

SRC_BLTIN		=	ft_echo.c			\
					ft_cd.c				\
					ft_pwd.c			\
					ft_env.c

SRC_PARCER		=	ft_read_command.c

SRC_EXECUTE		=	ft_execute.c

SRC_UTILS		=	ft_env_get.c		\
					ft_color_print.c	\
					ft_end.c 

#			Object and dependence files
OBJ				=	$(addprefix $(DIR_OBJ), $(SRC:.c=.o))			\
					$(addprefix $(DIR_OBJ), $(SRC_ERR:.c=.o))		\
					$(addprefix $(DIR_OBJ), $(SRC_BLTIN:.c=.o))		\
					$(addprefix $(DIR_OBJ), $(SRC_PARCER:.c=.o))	\
					$(addprefix $(DIR_OBJ), $(SRC_EXECUTE:.c=.o))	\
					$(addprefix $(DIR_OBJ), $(SRC_UTILS:.c=.o))

DEP				=	$(OBJ:.o=.d)

#			Main directories
DIR_OBJ			=	obj/
DIR_SRC			=	srcs/
DIR_INC			=	includes/
DIR_LIBFT		=	libft/
DIR_INC_LIB		=	$(DIR_LIBFT)$(DIR_INC)
DIR_ERROR		=	$(addprefix $(DIR_SRC), errors/)
DIR_BLTIN		=	$(addprefix $(DIR_SRC), builtins/)
DIR_PARCER		=	$(addprefix $(DIR_SRC), parcer/)
DIR_EXECUTE		=	$(addprefix $(DIR_SRC), executer/)
DIR_UTILS		=	$(addprefix $(DIR_SRC), utils/)
	
#			Main libraries
LFT				=	$(DIR_LIBFT)libft.a

#			Executeble name of Norm
NORM			=	norminette

#			Main variables
CC				=	gcc
CFLAGS			=	-I $(DIR_INC) -I $(DIR_INC_LIB)		\
					-Wall -Wextra -Werror	\
					-MMD #-fsanitize=address
RM				=	rm -f
COMPILE_C		=	$(CC) -c $(CFLAGS) -o $@ $<

ifeq ($(DEBUG), YES)
CFLAGS			+= -g
endif

all: $(NAME)

-include $(DEP)

$(NAME): $(DIR_OBJ) $(LFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(DIR_LIBFT) -lft -o $@

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	$(COMPILE_C)

$(DIR_OBJ)%.o: $(DIR_ERROR)%.c
	$(COMPILE_C)

$(DIR_OBJ)%.o: $(DIR_BLTIN)%.c
	$(COMPILE_C) 

$(DIR_OBJ)%.o: $(DIR_PARCER)%.c
	$(COMPILE_C) 

$(DIR_OBJ)%.o: $(DIR_EXECUTE)%.c
	$(COMPILE_C) 

$(DIR_OBJ)%.o: $(DIR_UTILS)%.c
	$(COMPILE_C) 

clean:
	$(RM)r $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean_all all

clean_libft:
	$(MAKE) clean -C $(DIR_LIBFT)

fclean_libft:
	$(MAKE) fclean -C $(DIR_LIBFT)

$(LFT): make_libft

make_libft:
	$(MAKE) -C $(DIR_LIBFT) --no-print-directory 

norm:
	$(NORM) $(DIR_LIBFT)*.c
	$(NORM) $(OBJ:.o=.c)
	$(NORM) $(DIR_INC)

re_all: fclean_libft fclean  all

clean_all: clean_libft clean 

fclean_all: fclean_libft fclean 

debug:
	$(MAKE) DEBUG=YES re --no-print-directory

test: all
	./$(NAME)

valgrind: all
	valgrind --leak-check=full	\
	--show-leak-kinds=all --track-origins=yes \
	--verbose ./$(NAME)

.PHONY: all norm make_libft re re_all		\
		fclean_all clean_all fclean clean 	\
		fclean_libft clean_libft

.SILENT: norm make_libft