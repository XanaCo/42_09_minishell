# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 18:07:11 by ancolmen          #+#    #+#              #
#    Updated: 2023/07/31 12:40:21 by ancolmen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######	VARIABLES #######

NAME		= minishell

LIBFT		= libft.a

LFT_PATH	= ./libft/
SRC_PATH	= ./src/
BIN_PATH 	= ./bin/

SRC			= main.c \
			parsing/1_lexer.c \
			parsing/2_parser.c \
			parsing/3_tree_structure.c \
			parsing/4_heredoc.c \
			parsing/5_heredoc_utils.c \
			parsing/5_quotes.c \
			parsing/6_var_env.c \
			parsing/utils_1.c \
			parsing/utils_2.c \
			gar/garbage.c \
			gar/garbage_utils.c \
			env/env.c \
			env/env_utils.c \
			signals/signal_parent.c \
			signals/signal_child.c \
			signals/signal_hd.c \
			utils/exit.c \
			utils/error_handling.c \
			utils/utils.c \
			exec/start_exec.c \
			exec/redir.c \
			exec/exec_process.c \
			exec/exec_process_utils.c \
			exec/exec_prep.c \
			exec/exec_cmd.c \
			builtin/bltn_cd.c \
			builtin/bltn_echo.c \
			builtin/bltn_env.c \
			builtin/bltn_exit.c \
			builtin/bltn_export.c \
			builtin/bltn_pwd.c \
			builtin/bltn_unset.c \
			debug/print_checks.c \
			debug/print_tree.c \
			debug/data_tests.c			

OBJ			= $(addprefix $(BIN_PATH), $(SRC:.c=.o))

DEPS		= $(OBJ:.o=.d)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -MMD -MP

CLIB 		= -Llibft -lft -lreadline

RM			= rm -rf

LEAKS		= valgrind

LF			= --leak-check=full \
        	--show-leak-kinds=all \
    		--track-origins=yes \
			--track-fds=yes \

SUP			= --suppressions=notes/valgrind_readline_leaks_ignore.supp

#######	RULES #######

all: $(NAME)

$(BIN_PATH)%.o: $(SRC_PATH)%.c
	@ mkdir -p $(dir $@)
	@ echo "\n\033[97;4m🚧 compiling $@ file 🚧\033[0m\n"
	@ $(CC) $(CFLAGS) -c $< -o $@
	@ echo "\033[32;1m★ bin OK ★\033[0m\n"
	
$(LFT_PATH)$(LIBFT):
	@ echo "\n\033[97;4m🚧 creating libft 🚧\033[0m\n"
	@ make --no-print-directory -C $(LFT_PATH)
	@ echo "\033[32;1m\n★ LIBFT OK ★\033[0m\n"

$(NAME): $(OBJ) $(LFT_PATH)$(LIBFT)
	@ echo "\033[97;4m🚧 minishell in progress 🚧\033[0m\n"
	@ $(CC) $(CFLAGS) $(OBJ) $(CLIB) -o $(NAME)
	@ echo "\033[32;1m✅ MINISHELL READY ✅\033[0m\n"

bonus: all

clean:
	@ echo "\n\033[97;4m🚧 cleaning object files 🚧\033[0m\n"
	@ make clean --no-print-directory -C $(LFT_PATH)
	@ $(RM) $(BIN_PATH)
	@ echo "\033[32;1m★ objects cleaned ★\033[0m\n"
	

fclean: clean
	@ make fclean --no-print-directory -C $(LFT_PATH)
	@ $(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

# leaks: all
# 	$(LEAKS) $(SUP) ./$(NAME)

# leaksfull: all
# 	$(LEAKS) $(LF) $(SUP) ./$(NAME)

.PHONY: all clean fclean re bonus rebonus

-include $(DEPS)
