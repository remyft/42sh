# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/28 20:50:45 by rfontain          #+#    #+#              #
#    Updated: 2019/03/02 16:13:31 by dbaffier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-ansi -pedantic -Wmissing-prototypes

LIBFT_PATH = libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
LIBFT_LINK = -L$(LIBFT_PATH) -lft -lncurses

PRINTF_PATH = ft_printf
PRINTF_LIB = $(PRINTF_PATH)/ft_printf.a
PRINTF_LINK = -L$(PRINTF_PATH) -lprintf

INC_DIR = include
INCS = -I$(PRINTF_PATH)/$(INC_DIR) -I$(LIBFT_PATH)/$(INC_DIR) -I$(INC_DIR)

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS_DIR = .deps/
DEPS = $(addprefix $(DEPS_DIR), $(SRCS:.c=.d))

RM = /bin/rm -rf

SHELL := /bin/bash

# SHELL
SRCS_DIR = src/
SRCS =	shell.c								\

# ENVIRONMENT
ENV_DIR = $(SRCS_DIR)environment/
SRCS += collect_env.c						\
		free_shell_env.c					\
		shell_env.c							\

# LINE EDITION
LINE_DIR = $(SRCS_DIR)line_edition/
SRCS += create_hdoc.c						\
		deal_hdoc.c							\
		deal_line.c							\
		deal_typing.c						\
		deal_struct.c						\
		main_tools.c						\
		reset_line.c						\
		signal.c							\
		tools.c								\

# COMPLETION
CMPL_DIR = $(SRCS_DIR)completion/
SRCS += completion_key.c					\
		color_put.c							\
		create_tree.c						\
		cpl_select_key.c					\
		deal_change.c						\
		deal_complet_tools.c				\
		deal_completion.c					\
		deal_put_tool.c						\
		deal_select_branch.c				\
		deal_select_tools.c					\
		feed_branch.c						\
		fill_tree.c							\
		get_completion.c					\
		get_comp_tools.c					\
		put_completion.c					\
		put_select_tools.c					\
		put_tree_tools.c					\
		put_tree.c							\
		reset_tree.c						\
		select_branch.c						\
		set_complet.c						\
		tree_tools.c						\

# TERMCAPS
TERM_DIR = $(SRCS_DIR)termcaps/
SRCS += control.c							\
		delete.c							\
		history.c							\
		line_move.c							\
		move_cursor.c						\
		move_history.c						\
		move_word.c							\
		term_properties.c					\
		term_tools.c						\
		typing.c							\

# USER INTERFACE
USER_DIR = $(SRCS_DIR)user_interface/
SRCS += ft_copy.c							\
		ft_cut.c							\
		ft_paste.c							\
		line_select.c						\
		select.c							\

# TOKENS
TOKEN_DIR = token/
SRCS += expand_word.c						\
		handle_alias.c						\
		handle_command.c					\
		handle_comment.c					\
		handle_end_of_input.c				\
		handle_equal.c						\
		handle_minus.c						\
		handle_newline.c					\
		handle_operator.c					\
		handle_quote.c						\
		handle_subs.c						\
		handle_word.c						\
		identify_operator.c					\
		identify_word.c						\
		is_alias_valid_name.c				\
		is_subs_next.c						\
		is_subs.c							\
		is_token_next.c						\
		is_token_valid_name.c				\
		is_token.c							\
		remove_line_continuation.c			\
		token_debug.c						\
		token_free.c						\
		token_get.c							\
		token_new.c							\

# PARSER
PARSER_DIR = parser/
SRCS += parse_async.c						\
		parse_ao_list.c						\
		parse_argument.c					\
		parse_debug.c						\
		parse_error.c						\
		parse_free.c						\
		parse_io_number.c					\
		parse_list.c						\
		parse_new_functions.c				\
		parse_newline.c						\
		parse_operator.c					\
		parse_pipe.c						\
		parse.c								\

# COMMAND
COMMAND_DIR = command/
SRCS += command_access.c					\
		command_builtin.c					\
		command_check.c						\
		command_debug.c						\
		command_error.c						\
		command_system.c					\
		command_free.c						\
		command_group_command.c				\
		command_group_env.c					\
		command_list.c						\
		command_parse.c						\
		command_path.c						\
		command_pipe.c						\
		command_prepare.c					\
		command_redirect.c					\
		command_restore_fds.c				\
		command_save_fds.c					\
		command_wait.c						\
		environment_modify.c				\
		quote_removal.c						\

# EXPANSIONS
EXPANSION_DIR = expansion/
SRCS += expand_debug.c						\
		expand_argument.c					\
		expand_arithmetic.c					\
		expand_backslash.c					\
		expand_backtick.c					\
		expand_dollar_do_expansion.c		\
		expand_dollar_get_action.c			\
		expand_dollar_parameter_init.c		\
		expand_dollar_parameter_value.c		\
		expand_dollar_parameter.c			\
		expand_dollar_special_next.c		\
		expand_dollar_special.c				\
		expand_dollar_substitution.c		\
		expand_dollar_word_value.c			\
		expand_dollar_word_nonnull_subst.c	\
		expand_dollar_word_null_assign.c	\
		expand_dollar_word_null_error.c		\
		expand_dollar_word_null_subst.c		\
		expand_dollar_word.c				\
		expand_dollar.c						\
		expand_dquote.c						\
		expand_end.c						\
		expand_error.c						\
		expand_error_functions1.c			\
		expand_error_functions2.c			\
		expand_error_functions3.c			\
		expand_fieldsplit.c					\
		expand_free_t_ret.c					\
		expand_glob.c						\
		expand_loop.c						\
		expand_math.c						\
		expand_squote.c						\
		expand_subshell.c					\
		expand_tilde_comparaison.c			\
		expand_tilde_functions.c			\
		expand_tilde.c						\
		is_expansion.c						\
		param_addchar.c						\
		param_addstr.c						\

# REDIRECTIONS
REDIRECTION_DIR = redirection/
SRCS += redirect_and_dgreat.c				\
		redirect_and_great.c				\
		redirect_dgreat.c					\
		redirect_dless.c					\
		redirect_error.c					\
		redirect_great_and.c				\
		redirect_great_pipe.c				\
		redirect_great.c					\
		redirect_less_and.c					\
		redirect_less_great.c				\
		redirect_less.c						\
		redirect_open_error.c				\
		redirection.c						\

# BUILTINS
BUILTIN_DIR = builtin/
SRCS += builtin_alias_error.c				\
		builtin_alias_get.c					\
		builtin_alias_new.c					\
		builtin_alias_set_value.c			\
		builtin_alias_set.c					\
		builtin_alias.c						\
		builtin_cd_change.c					\
		builtin_cd_error.c					\
		builtin_cd_recreate.c				\
		builtin_cd_search.c					\
		builtin_cd_write.c					\
		builtin_cd.c						\
		builtin_echo.c						\
		builtin_env_error.c					\
		builtin_env_exec.c					\
		builtin_env_free_opt.c				\
		builtin_env_opt_i.c					\
		builtin_env_opt_p.c					\
		builtin_env_opt_u.c					\
		builtin_env_opt_v.c					\
		builtin_env_options.c				\
		builtin_env.c						\
		builtin_exit.c						\
		builtin_setenv.c					\
		builtin_unalias.c					\
		builtin_unsetenv.c					\

# LIBRARY
LIBRARY_DIR = lib/
SRCS += sh_is_escapable.c					\
		sh_freestr.c						\
		sh_freetab.c						\
		sh_getnenv.c						\
		sh_getnenvaddr.c					\
		sh_newenv.c							\
		sh_putendl_fd.c						\
		sh_putstr_fd.c						\
		sh_puttab.c							\
		sh_setenv.c							\
		sh_str_isescape.c					\
		sh_stralnum.c						\
		sh_strchr.c							\
		sh_strncmp.c						\
		sh_strnjoin.c						\
		sh_strrchr.c						\
		sh_tabdup.c							\
		sh_tablen.c							\
		sh_unsetenv.c						\

# GLOBING
GLOB_DIR = $(SRCS_DIR)globing/
SRCS += check_glob.c						\
		check_tool.c						\
		fill_glob.c							\
		get_glob.c							\
		get_tools.c							\
		glob_tools.c						\
		globing.c							\

#JOB_CONTROL
JOB_DIR = job_control/
SRCS	+= job_insert.c						\
		   job_status.c						\
		   job_terminated.c					\
		   job_utils.c						\

COL			=	$$(tput cols)/3
DIRNAME		=	$$(basename $$(pwd))
DIRNAMELEN	=	$$(basename $$(pwd) | tr -d '\n' | wc -m )
MOON		=	$$(echo 🌝)
CLOCK		=	$$(echo 🕛)
DELTA		=	$$(echo "$$(tput cols)-$(COL)-$(DIRNAMELEN)-20"|bc)
NB			=	$(words $(SRCS))
MAX			=	$$(echo "$(NB) - 1"|bc)
INDEX		=	0
TSITSI = 	$(eval DONE=$(shell echo $$(($(INDEX)*$(COL)/$(NB)))))  \
	$(eval PERCENT=$(shell echo $$(($(INDEX)*101/$(NB)))))  \
	$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))  \
	$(eval TO_DO=$(shell echo $$(($(COL)-$(INDEX)*$(COL)/$(NB)))))  \
	$(eval MOON=$(shell if [ $(INDEX) == $(MAX) ]; then echo 🌞; \
							elif [ $(MOON) == 🌝 ]; then echo 🌔; \
							elif [ $(MOON) == 🌔 ]; then echo 🌓; \
							elif [ $(MOON) == 🌓 ]; then echo 🌒; \
							elif [ $(MOON) == 🌒 ]; then echo 🌚; \
							elif [ $(MOON) == 🌚 ]; then echo 🌘; \
							elif [ $(MOON) == 🌘 ]; then echo 🌗; \
							elif [ $(MOON) == 🌗 ]; then echo 🌖; \
							elif [ $(MOON) == 🌖 ]; then echo 🌝; fi )) \
	$(eval CLOCK=$(shell if [ $(INDEX) == $(MAX) ]; then echo 💥; \
							elif [ $(CLOCK) == 🕛 ]; then echo 🕑; \
							elif [ $(CLOCK) == 🕑 ]; then echo 🕒; \
							elif [ $(CLOCK) == 🕒 ]; then echo 🕔; \
							elif [ $(CLOCK) == 🕔 ]; then echo 🕕; \
							elif [ $(CLOCK) == 🕕 ]; then echo 🕗; \
							elif [ $(CLOCK) == 🕗 ]; then echo 🕘; \
							elif [ $(CLOCK) == 🕘 ]; then echo 🕙; \
							elif [ $(CLOCK) == 🕙 ]; then echo 🕛; fi )) \
	printf "\r\033[38;5;11m%s  MAKE : %3d%% \033[48;5;%dm%*s\033[0m%*s%s  21sh/%.*s\033[0m\033[K" $(MOON) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(CLOCK) $(DELTA) "$<" \
	$(eval INDEX=$(shell echo $$(($(INDEX)+1)))) \

RESET	= \x1b[0m
GREY	= \x1b[1;30m
RED		= \x1b[1;31m
GREEN	= \x1b[0;32m
YELLOW	= \x1b[0;33m
OK =	$(GREEN)[ OK ]$(RESET)
NEWLINE = $(shell echo "")

all: $(OBJS_DIR) $(DEPS_DIR) $(LIBFT_LIB) $(PRINTF_LIB) $(NAME)

$(OBJS_DIR):
	@mkdir -p $@

$(DEPS_DIR):
	@mkdir -p $@

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(PRINTF_LIB):
	@make -C $(PRINTF_PATH)

$(NAME): $(NEWLINE) $(OBJS)
	@$(CC) $^ -o $@ $(LIBFT_LINK) $(PRINTF_LINK) $(DEBUG)
	@echo -e "\n$(GREEN) Compiling $(YELLOW)[ $(RESET)$(NAME)$(YELLOW) ] $(OK) $(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(PARSER_DIR) -I$(INC_DIR)/$(EXPANSION_DIR) -I$(INC_DIR)/$(COMMAND_DIR) -I$(INC_DIR)/$(JOB_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(ENV_DIR)%.c
$(OBJS_DIR)%.o: $(ENV_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(LIBRARY_DIR) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(JOB_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(LINE_DIR)%.c
$(OBJS_DIR)%.o: $(LINE_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(LIBRARY_DIR) -I$(INC_DIR)/$(JOB_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)deal_hdoc.o: INCS += -I$(INC_DIR)/$(TOKEN_DIR)
$(OBJS_DIR)create_hdoc.o: INCS += -I$(INC_DIR)/$(TOKEN_DIR)

$(OBJS_DIR)%.o: $(CMPL_DIR)%.c
$(OBJS_DIR)%.o: $(CMPL_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(LIBRARY_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(USER_DIR)%.c
$(OBJS_DIR)%.o: $(USER_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(BUIL_DIR)%.c
$(OBJS_DIR)%.o: $(BUIL_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(TERM_DIR)%.c
$(OBJS_DIR)%.o: $(TERM_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(TOKEN_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(TOKEN_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(BUILTIN_DIR) -I$(INC_DIR)/$(JOB_DIR) $(DEBUG)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(PARSER_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(PARSER_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(PARSER_DIR) -I$(INC_DIR)/$(ALIAS_DIR) -I$(INC_DIR)/$(JOB_DIR) $(DEBUG)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(EXPANSION_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(EXPANSION_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(PARSER_DIR) -I$(INC_DIR)/$(EXPANSION_DIR) -I$(INC_DIR)/$(REDIRECTION_DIR) -I$(INC_DIR)/$(LIBRARY_DIR) -I$(INC_DIR)/$(ALIAS_DIR) -I$(INC_DIR)/$(JOB_DIR) -I$(INC_DIR)/$(COMMAND_DIR) $(DEBUG)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(COMMAND_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(COMMAND_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(COMMAND_DIR) -I$(INC_DIR)/$(PARSER_DIR) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(EXPANSION_DIR) -I$(INC_DIR)/$(REDIRECTION_DIR) -I$(INC_DIR)/$(BUILTIN_DIR) -I$(INC_DIR)/$(LIBRARY_DIR) -I$(INC_DIR)/$(ALIAS_DIR) -I$(INC_DIR)/$(JOB_DIR) $(DEBUG)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(REDIRECTION_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(REDIRECTION_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(REDIRECTION_DIR) -I$(INC_DIR)/$(PARSER_DIR) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(ALIAS_DIR) -I$(INC_DIR)/$(JOB_DIR) $(DEBUG)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(BUILTIN_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(BUILTIN_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(BUILTIN_DIR) -I $(INC_DIR)/$(COMMAND_DIR) -I$(INC_DIR)/$(EXPANSION_DIR) -I$(INC_DIR)/$(PARSER_DIR) -I$(INC_DIR)/$(LIBRARY_DIR) -I$(INC_DIR)/$(TOKEN_DIR) -I$(INC_DIR)/$(ALIAS_DIR) -I$(INC_DIR)/$(JOB_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(LIBRARY_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(LIBRARY_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(LIBRARY_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(GLOB_DIR)%.c
$(OBJS_DIR)%.o: $(GLOB_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(JOB_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(JOB_DIR)%.c $(DEPS_DIR)%.d
	@$(TSITSI)
	@$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS) -I$(INC_DIR)/$(JOB_DIR) -I$(INC_DIR)/$(COMMAND_DIR) -I$(INC_DIR)/$(PARSER_DIR)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(DEPS_DIR)%.d: ;
.PRECIOUS: $@

-include $(DEPS)

clean:
	@$(RM) $(OBJS_DIR)
	@$(RM) $(DEPS_DIR)
#	@make -C $(LIBFT_PATH) clean
	@echo -e "$(RED) Cleaning : $(YELLOW)[ $(RESET)$(NAME)$(YELLOW) ] $(OK)"

fclean: clean
	@$(RM) $(NAME)
#	@make -C $(LIBFT_PATH) fclean
	@echo -e "$(RED) Deleting..$(YELLOW) [ $(RESET)$(NAME)$(YELLOW) ] $(OK)"

re: fclean all

debug: DEBUG = -g3 -fsanitize=address -DDEBUG -g
debug: re

nn:
	norminette $(SRCS)
	norminette $(INC_DIR)

.PHONY: clean fclean all re
