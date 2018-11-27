# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/28 20:50:45 by rfontain          #+#    #+#              #
#    Updated: 2018/11/27 22:08:38 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

RM = rm -rf

RED = "\x1b[0;31;40m"
RESET = "\x1b[1;37;40m"
GREY = "\x1b[1;30;40m"
GREEN = "\x1b[1;32;40m"

LIB_PATH = libft
LIB = $(LIB_PATH)/libft.a
LIB_LINK = -L$(LIB_PATH) -lft -lncurses

INC_DIR = include
INCS = -I$(LIB_PATH)/$(INC_DIR) -I$(INC_DIR)

BUIL_DIR = $(SRCS_DIR)builtin/

OTHR_DIR = $(SRCS_DIR)other/

SRCS_DIR = src/
SRCS =	minishell.c			\
		deal_commande.c		\
		tools.c				\
		setenv_builtin.c	\
		cd_builtin.c		\
		exec.c				\
		main_tools.c		\
		signal.c			\
		welcome.c			\

#COMPLETION
CMPL_DIR = $(SRCS_DIR)completion/
SRCS +=	create_tree.c		\
		deal_completion.c	\
		put_completion.c	\
		put_select_tools.c	\
		put_tree_tools.c	\
		tree_tools.c		\
		reset_tree.c		\

#TERMCAPS
TERM_DIR = $(SRCS_DIR)termcaps/
SRCS += term_properties.c	\
		move_cursor.c		\
		term_tools.c		\
		history.c			\
		move_history.c		\
		control.c			\
		delete.c			\
		move_word.c			\
		typing.c			\
		select.c			\

#TOKENS
TOKEN_DIR = token/
SRCS += define_token.c		\
		get_commands.c		\
		get_tokens.c		\
		identify_operator.c	\
		identify_token.c	\
		is_token.c			\
		new_token.c			\
		operator_handler.c	\
		quote_handler.c		\
		word_handler.c		\

OK =	$(GREEN)[OK]$(RESET)

NEWLINE = $(shell echo "")

CFLAGS =  -Wall -Wextra -Werror -std=gnu99

DEBUG = -g3 -fsanitize=address

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS_DIR = .deps/
DEPS = $(addprefix $(DEPS_DIR), $(SRCS:.c=.d))

all: $(OBJS_DIR) $(DEPS_DIR) $(LIB) $(NAME)

$(OBJS_DIR):
	mkdir -p $@

$(DEPS_DIR):
	mkdir -p $@

$(LIB):
	make -C $(LIB_PATH)

$(NAME): $(NEWLINE) $(OBJS) $(LIB)
	@$(CC) $^ -o $@ $(LIB_LINK) #$(DEBUG)
	@echo ""
	@echo $(GREY)" Compilling" $(RESET) [ $(NAME) ] $(OK)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(DEPS_DIR)%.d
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -I$(INC_DIR)/$(TOKEN_DIR) -o $@ -c $< 

$(OBJS_DIR)%.o: $(CMPL_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(OBJS_DIR)%.o: $(BUIL_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(OBJS_DIR)%.o: $(TERM_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(OBJS_DIR)%.o: $(SRCS_DIR)$(TOKEN_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -I$(INC_DIR)/$(TOKEN_DIR) -o $@ -c $< 

$(OBJS_DIR)%.o: $(OTHR_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(DEPS_DIR)%.d: ;
.PRECIOUS: $@

-include $(DEPS)

clean:
	@$(RM) $(OBJS_DIR)
	@$(RM) $(DEPS_DIR)
#	@make -C $(LIB_PATH) clean
	@echo $(GREY)" Cleaning :" $(RESET) [ $(NAME) ] $(OK)

fclean: clean
	@$(RM) $(NAME)
#	@make -C $(LIB_PATH) fclean
	@echo $(GREY)" Deleting.." $(RESET) [ $(NAME) ] $(OK)

re: fclean all

nn:
	norminette $(SRCS)
	norminette $(INC_DIR)

.PHONY: clean fclean all re
