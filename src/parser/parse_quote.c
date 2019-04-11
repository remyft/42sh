/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:48:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/11 17:56:56 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "parser_errors.h"
#include "main_tools.h"
#include "shell.h"

static char		*get_new_prompt(t_quote *head)
{
	static char	*prompt[] = {
		DEFAULT_PROMPT, BACKSLASH_PROMPT, DQUOTE_PROMPT, SQUOTE_PROMPT,
		BRACE_PROMPT, D_BRACE_PROMPT, PARENTHESE_PROMPT, D_PARENTHESE_PROMPT,
		BACKQUOTE_PROMPT, HERE_DOC_PROMPT,
	};
	char		*ret;
	int			i;

	ret = NULL;
	while (head)
	{
		if (ret && !(ret = ft_strjoinfree(ret, " ", 1)))
			return (NULL);
		i = head->type;
		if (!(ret = (ret) ?
			ft_strjoinfree(ret, prompt[i], 1) : ft_strdup(prompt[i])))
			return (NULL);
		head = head->next;
	}
	ret = (ret) ? ft_strjoinfree(ret, prompt[0], 1) : ft_strdup(prompt[0]);
	return (ret);
}

static int		get_new_input(t_quote *quote, t_line **line)
{
	char		*promptsave;

	if (!(*line = get_struct()))
		return (ERR_MALLOC_FAILED);
	promptsave = (*line)->prompt;
	init_new_buff(*line);
	if (!((*line)->prompt = get_new_prompt(quote)))
		return (ERR_MALLOC_FAILED);
	(*line)->lprompt = ft_strlen((*line)->prompt);
	(*line)->curr->quoted = 1;
	put_prompt((*line)->prompt, (*line)->ret);
	(*line)->tmp[0] = 0;
	while ((*line)->shell_loop && (*line)->tmp[0] == 0)
		deal_typing(*line);
	write(STDIN_FILENO, "\n", 1);
	(*line)->shell_loop = 1;
	(*line)->curr->quoted = 0;
	ft_strdel(&(*line)->prompt);
	(*line)->prompt = promptsave;
	(*line)->lprompt = ft_strlen((*line)->prompt);
	if ((*line)->tmp[0] == -1)
		return (ERR_FREE_ALL);
	if ((*line)->tmp[0] == 4)
		return (ERR_MISSING_QUOTE);
	return (ERR_NONE);
}

static int		tokenise_quote(t_token *token, t_line *line, t_n_input *input,
char **cmdline)
{
	static int	(*handler[])(t_token *, t_line *, t_n_input *) = {
		aliased_line, bslashed_line, dquoted_line, squoted_line, braced_line,
		dbraced_line, parenthed_line, dparenthed_line, backquoted_line,
	};

	if (handler[input->type](token, line, input)
	|| !(*cmdline = ft_strjoin(input->linesave, line->curr->buff)))
		return (ERR_MALLOC_FAILED);
	free_token(input->token);
	*input->token = tokenise((const char *)*cmdline, input->e);
	ft_strdel(&input->linesave);
	return (ERR_NONE);
}

int				parse_quote(char **cmdline, t_token **token, t_s_env *e)
{
	t_n_input	input;
	t_token		*ptr;
	t_line		*line;

	input.e = e;
	input.token = token;
	if (cmdline && (ptr = *token))
		while (ptr)
		{
			if ((input.type = quote_type(ptr->quote)) != NO_QUOTE)
			{
				if (!e->interactive)
					return (!parse_error(ERR_MISSING_QUOTE, ptr, e));
				if ((input.error = get_new_input(ptr->quote, &line)))
					return (!parse_error(input.error, ptr, e));
				input.linesave = *cmdline;
				*cmdline = NULL;
				if ((input.error = tokenise_quote(ptr, line, &input, cmdline)))
					return (!parse_error(input.error, NULLTOKEN, e));
				ptr = *input.token;
			}
			else
				ptr = ptr->next;
		}
	return (ERR_NONE);
}
