# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/28 20:50:45 by rfontain          #+#    #+#              #
#    Updated: 2018/12/11 14:56:43 by gbourgeo         ###   ########.fr        #
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
		singleton.c			\
		welcome.c			\
		remove_line_continuation.c	\

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
SRCS += expand_word.c			\
		get_tokens.c			\
		get_subs.c				\
		handle_comment.c		\
		handle_end_of_input.c	\
		handle_newline.c		\
		handle_operator.c		\
		handle_quote.c			\
		handle_subs.c			\
		handle_word.c			\
		identify_operator.c		\
		identify_word.c			\
		is_subs.c				\
		is_subs2.c				\
		is_token.c				\
		is_token2.c				\
		new_token.c				\

#PARSER
PARSER_DIR = parser/
SRCS += parse.c				\

OK =	$(GREEN)[OK]$(RESET)

NEWLINE = $(shell echo "")

CFLAGS =  -Wall -Wextra -Werror -std=gnu99

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
	@$(CC) $(DEBUG) $^ -o $@ $(LIB_LINK)
	@echo ""
	@echo $(GREY)" Compilling" $(RESET) [ $(NAME) ] $(OK)


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(DEPS_DIR)%.d
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) $(DEBUG) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)minishell.o: INCS += -I$(INC_DIR)/$(TOKEN_DIR)
$(OBJS_DIR)minishell.o: INCS += -I$(INC_DIR)/$(PARSER_DIR)

$(OBJS_DIR)%.o: $(CMPL_DIR)%.c
$(OBJS_DIR)%.o: $(CMPL_DIR)%.c $(DEPS_DIR)%.d
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(BUIL_DIR)%.c
$(OBJS_DIR)%.o: $(BUIL_DIR)%.c $(DEPS_DIR)%.d
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(TERM_DIR)%.c
$(OBJS_DIR)%.o: $(TERM_DIR)%.c $(DEPS_DIR)%.d
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(TOKEN_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(TOKEN_DIR)%.c $(DEPS_DIR)%.d
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< \
	$(INCS) -I$(INC_DIR)/$(TOKEN_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(PARSER_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(PARSER_DIR)%.c $(DEPS_DIR)%.d
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< \
	$(INCS) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(PARSER_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(OTHR_DIR)%.c
$(OBJS_DIR)%.o: $(OTHR_DIR)%.c $(DEPS_DIR)%.d
	@echo $(RED)" ᚘ  "$(RESET) | tr -d '\n'
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

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

debug: DEBUG = -g3 -fsanitize=address -DDEBUG -g
debug: re

nn:
	norminette $(SRCS)
	norminette $(INC_DIR)

.PHONY: clean fclean all re
