# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 19:31:28 by imedgar           #+#    #+#              #
#    Updated: 2020/11/09 11:19:04 by imedgar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#			The main programm
NAME			=	minishell

#			Source files
SRC				=	main.c

SRC_ERR			=	ft_error.c

SRC_BLTIN		=	ft_echo.c	\
					ft_cd.c		\
					ft_pwd.c

#			Header files
INCLUDES		=	minishell.h

#			Object and dependence files
OBJ				=	$(addprefix $(DIR_SRC), $(SRC:.c=.o))		\
					$(addprefix $(DIR_ERROR), $(SRC_ERR:.c=.o))	\
					$(addprefix $(DIR_BLTIN), $(SRC_BLTIN:.c=.o))
DEP				=	$(OBJ:.o=.d)

#			Main directories
DIR_SRC			=	./srcs/
DIR_INC			=	./includes/
DIR_LIBFT		=	./libft/
DIR_ERROR		=	$(addprefix $(DIR_SRC), errors/)
DIR_BLTIN		=	$(addprefix $(DIR_SRC), builtins/)

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

$(NAME): $(LFT) $(OBJ)
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

$(LFT): make_libft

norm:
	$(NORM) $(DIR_LIBFT)*.[ch]
	$(NORM) $(addprefix $(DIR_SRC), $(SRC)) \
	$(addprefix $(DIR_INC), $(INCLUDES))

re_all: fclean fclean_libft all

clean_all: clean clean_libft

fclean_all: fclean fclean_libft

.PHONY: all norm make_libft re re_all		\
		fclean_all clean_all fclean clean 	\
		fclean_libft clean_libft