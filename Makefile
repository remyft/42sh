# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfontain <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/28 20:50:45 by rfontain          #+#    #+#              #
#    Updated: 2018/11/23 07:17:29 by rfontain         ###   ########.fr        #
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
LIB_LINK = -L $(LIB_PATH) -lft -lncurses

INC_DIR = include
INCS = -I $(LIB_PATH)/ -I $(INC_DIR)

SRCS_DIR = src/

CMPL_DIR = $(SRCS_DIR)completion/

TERM_DIR = $(SRCS_DIR)termcaps/

BUIL_DIR = $(SRCS_DIR)builtin/

OTHR_DIR = $(SRCS_DIR)other/

SRCS =	minishell.c			\
		deal_commande.c		\
		tools.c				\
		setenv_builtin.c	\
		cd_builtin.c		\
		exec.c				\
		main_tools.c		\
		signal.c			\

#COMPLETION
SRCS +=	create_tree.c		\
		deal_completion.c	\
		put_completion.c	\
		put_select_tools.c	\
		put_tree_tools.c	\
		tree_tools.c		\
		reset_tree.c		\

#TERMCAPS
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

OK =      $(GREEN)[OK]$(RESET)		

NEWLINE = $(shell echo "")

CFLAGS +=  -Wall -Wextra -Werror

DEBUG += -fsanitize=address

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@mkdir -p $@

$(NAME): $(NEWLINE) $(OBJS) $(LIB)
	@$(CC) $^ -o $@ $(LIB_LINK) #$(DEBUG)
	@echo ""
	@echo $(GREY)" Compilling" $(RESET) [ $(NAME) ] $(OK)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(OBJS_DIR)%.o: $(CMPL_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(OBJS_DIR)%.o: $(BUIL_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(OBJS_DIR)%.o: $(TERM_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(OBJS_DIR)%.o: $(OTHR_DIR)%.c
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< 

$(LIB):
	@echo ""
	@echo " " | tr -d '\n'
	@make -C $(LIB_PATH)

clean:
	@$(RM) $(OBJS_DIR)
	@make -C $(LIB_PATH) clean
	@echo $(GREY)" Cleaning :" $(RESET) [ $(NAME) ] $(OK)

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo $(GREY)" Deleting.." $(RESET) [ $(NAME) ] $(OK)

reclean: clean
	@$(RM) $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo $(GREY)" Deleting.." $(RESET) [ $(NAME) ] $(OK)
	@echo ""

re: reclean all

nn:
	norminette $(SRCS)
	norminette $(INC_DIR)

.PHONY: clean fclean all re
