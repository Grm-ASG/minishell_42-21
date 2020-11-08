# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 19:31:28 by imedgar           #+#    #+#              #
#    Updated: 2020/11/08 22:54:14 by imedgar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#			The main programm
NAME			=	minishell

#			Source files
SRC				=	main.c

#			Header files
INCLUDES		=	minishell.h

#			Object and dependence files
OBJ				=	$(addprefix $(DIR_SRC), $(SRC:.c=.o))
DEP				=	$(addprefix $(DIR_SRC), $(SRC:.c=.d))

#			Main directories
DIR_SRC			=	./srcs/
DIR_INC			=	./includes/
DIR_LIBFT		=	./libft/

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
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(DIR_LIBFT) -lft

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: fclean all

clean_libft:
	$(MAKE) clean -C $(DIR_LIBFT)

fclean_libft:
	$(MAKE) fclean -C $(DIR_LIBFT)

make_libft:
	$(MAKE) -C $(DIR_LIBFT)

norm:
	$(NORM) $(DIR_LIBFT)*.[ch]
	$(NORM) $(addprefix $(DIR_SRC), $(SRC)) \
	$(addprefix $(DIR_INC), $(INCLUDES))

$(LFT): make_libft

re_all: fclean fclean_libft all

clean_all: clean clean_libft

fclean_all: fclean fclean_libft

.PHONY: all norm make_libft re re_all		\
		fclean_all clean_all fclean clean 	\
		fclean_libft clean_libft