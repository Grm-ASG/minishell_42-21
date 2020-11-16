# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 19:31:28 by imedgar           #+#    #+#              #
#    Updated: 2020/11/16 13:50:58 by imedgar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#			The main programm
NAME			=	minishell

#			Source files
SRC				=	main.c

SRC_ERR			=	ft_error.c

SRC_BLTIN		=	ft_echo.c	\
					ft_cd.c		\
					ft_pwd.c	\
					ft_env.c

SRC_GNL			=	get_next_line.c	\
					get_next_line_utils.c

SRC_PARCER		=	ft_read_command.c

SRC_EXECUTE		=	ft_execute.c

SRC_UTILS		=	ft_env_get.c

#			Header files
INCLUDES		=	minishell.h	\
					libft.h		\
					get_next_line.h

#			Object and dependence files
OBJ				=	$(addprefix $(DIR_SRC), $(SRC:.c=.o))				\
					$(addprefix $(DIR_GNL), $(SRC_GNL:.c=.o))			\
					$(addprefix $(DIR_ERROR), $(SRC_ERR:.c=.o))			\
					$(addprefix $(DIR_BLTIN), $(SRC_BLTIN:.c=.o))		\
					$(addprefix $(DIR_PARCER), $(SRC_PARCER:.c=.o))		\
					$(addprefix $(DIR_EXECUTE), $(SRC_EXECUTE:.c=.o))	\
					$(addprefix $(DIR_UTILS), $(SRC_UTILS:.c=.o))

DEP				=	$(OBJ:.o=.d)

#			Main directories
DIR_SRC			=	./srcs/
DIR_INC			=	./includes/
DIR_LIBFT		=	./libft/
DIR_GNL			=	./get_next_line/
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
CFLAGS			=	-g -I $(DIR_INC)		\
					-Wall -Wextra -Werror	\
					-MMD #-fsanitize=address
RM				=	rm -f

all: $(NAME)

-include $(DEP)

$(NAME): make_libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(DIR_LIBFT) -lft -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: fclean_all all

clean_libft:
	$(MAKE) clean -C $(DIR_LIBFT)

fclean_libft:
	$(MAKE) fclean -C $(DIR_LIBFT)

make_libft:
	$(MAKE) -C $(DIR_LIBFT)

norm:
	$(NORM) $(DIR_LIBFT)*.c
	$(NORM) $(OBJ:.o=.c)
	$(NORM) $(addprefix $(DIR_INC), $(INCLUDES))

re_all: fclean fclean_libft all

clean_all: clean clean_libft

fclean_all: fclean fclean_libft

valgrind: all
	valgrind --leak-check=full	\
	--show-leak-kinds=all --track-origins=yes \
	--verbose ./$(NAME)

.PHONY: all norm make_libft re re_all		\
		fclean_all clean_all fclean clean 	\
		fclean_libft clean_libft

.SILENT: norm