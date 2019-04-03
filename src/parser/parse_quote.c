/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:48:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/03 16:12:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "parser_errors.h"
#include "main_tools.h"

static char		*get_new_prompt(t_quote *head)
{
	static char	*prompt[] = {
		DEFAULT_PROMPT, BACKSLASH_PROMPT, DQUOTE_PROMPT, SQUOTE_PROMPT,
		BRACE_PROMPT, PARENTHESE_PROMPT, BACKQUOTE_PROMPT, HERE_DOC_PROMPT,
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
	put_prompt((*line)->prompt);
	(*line)->tmp[0] = 0;
	while ((*line)->tmp[0] == 0 || ((*line)->tmp[0] == 4))
		deal_typing(*line);
	write(STDIN_FILENO, "\n", 1);
	(*line)->curr->quoted = 0;
	ft_strdel(&(*line)->prompt);
	(*line)->prompt = promptsave;
	(*line)->lprompt = ft_strlen((*line)->prompt);
	if ((*line)->tmp[0] == -1)
		return (ERR_FREE_ALL);
	return (ERR_NONE);
}

static int		old_input_type(t_token *token, t_line *line, t_n_input *input)
{
	if (input->type == BACKSLASH)
	{
		input->linesave[ft_strlen(input->linesave) - 1] = '\0';
		token->len--;
	}
	else if (input->type == PARENTHESE)
	{
		if (*line->curr->buff
		&& ft_strncmp(token->head + token->len - 2, "$(", 2)
		&& line->curr->buff[0] != ')')
			if (!(input->linesave = ft_strjoinfree(input->linesave, ";", 1)))
				return (ERR_MALLOC_FAILED);
	}
	else if (input->type == BACKQUOTE)
	{
		if (*line->curr->buff
		&& token->head[token->len - 1] != '`'
		&& line->curr->buff[0] != '`')
			if (!(input->linesave = ft_strjoinfree(input->linesave, ";", 1)))
				return (ERR_MALLOC_FAILED);
	}
	else if (!(input->linesave = ft_strjoinfree(input->linesave, "\n", 1)))
		return (ERR_MALLOC_FAILED);
	return (ERR_NONE);
}

int				parse_quote(char **cmdline, t_token **token, t_s_env *e)
{
	t_n_input	input;
	t_token		*ptr;
	t_line		*line;

	if (cmdline && (ptr = *token))
		while (ptr)
		{
			if ((input.type = quote_type(ptr->quote)) != NO_QUOTE)
			{
				if ((input.error = get_new_input(ptr->quote, &line)) != ERR_NONE)
					return (!parse_error(input.error, NULLTOKEN, e));
				input.linesave = *cmdline;
				*cmdline = NULL;
				if (old_input_type(ptr, line, &input)
				|| !(*cmdline = ft_strjoin(input.linesave, line->curr->buff)))
					return (!parse_error(ERR_MALLOC_FAILED, ptr, e));
				free_token(token);
				*token = tokenise((const char *)*cmdline, e);
				ft_strdel(&input.linesave);
				ptr = *token;
			}
			else
				ptr = ptr->next;
		}
	return (ERR_NONE);
}
