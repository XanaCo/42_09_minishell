# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 12:39:51 by ancolmen          #+#    #+#              #
#    Updated: 2023/07/19 20:42:57 by ancolmen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######	VARIABLES

NAME		= libft.a

SRC_PATH	= ./src/
BIN_PATH	= ./bin/

SRC			= ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_striteri.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			get_next_line.c \
			ft_printf.c \
			ft_format_base.c \
			ft_putchar.c \
			ft_putnbr.c \
			ft_putnbr_u.c \
			ft_putnbr_base.c \
			ft_putptr.c \
			ft_putstr.c \
			ft_strrncmp.c \
			ft_countchar.c \
			ft_free_matrix.c \
			ft_iswspace.c \
			ft_abs.c \
			ft_strcmp.c \
			ft_atoi_ptr.c \
			ft_strcat.c

OBJ		= $(addprefix $(BIN_PATH), $(SRC:.c=.o))

DEPS 	= $(OBJ:.o=.d)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -MMD -MP

LIBC	= ar rc

RM 		= rm -rf

#######	RULES

all: $(NAME)

$(BIN_PATH)%.o : $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -c $< -o $@
	@echo "	Compiling " $<

$(NAME): $(OBJ)
	@$(LIBC) $(NAME) $(OBJ)
	@ranlib $(NAME)
	
clean:
	@$(RM) $(BIN_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)