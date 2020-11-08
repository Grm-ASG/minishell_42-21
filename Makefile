# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 19:31:28 by imedgar           #+#    #+#              #
#    Updated: 2020/11/08 19:45:23 by imedgar          ###   ########.fr        #
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

#			Executeble name of Norm
NORMINETTE		=	norminette

#			Main variables
CC				=	gcc
CFLAGS			=	-g -I $(DIR_INC) \
					-Wall -Wextra -Werror \
					-MMD #-fsanitize=address
RM				=	rm -rf

all: $(NAME)

-include $(DEP)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	$(NORMINETTE) $(addprefix $(DIR_SRC), $(SRC)) \
	$(addprefix $(DIR_INC), $(INCLUDES))

.PHONY: all clean fclean re norm