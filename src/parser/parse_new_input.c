/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:13:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/18 18:39:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "main_tools.h"
#include "parser_errors.h"
#include "parser.h"

static char		*get_prompt(t_quote *head)
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

#include "ft_printf.h"
static t_token	*get_token(t_token *token, char **line, char *oldl, t_s_env *e)
{
	t_token		*ret;

	ret = token;
	if (token)
		while (token->prev)
			token = token->prev;
	while (token)
	{
		token->head = *line + (token->head - oldl);
		token = token->next;
	}
	token = ret;
	if ((ret = tokenise(*line + ft_strlen(oldl) - token->len, e)))
	{
		ret->prev = token->prev;
		if (ret->prev)
			ret->prev->next = ret;
	}
	ft_strdel(&oldl);
	return (ret);
}

static int		get_new_input(t_token *token, t_line **line)
{
	char		*promptsave;

	if (!(*line = get_struct()))
		return (ERR_MALLOC_FAILED);
	promptsave = (*line)->prompt;
	init_new_buff(*line);
	if (!((*line)->prompt = get_prompt(token->quote)))
		return (ERR_MALLOC_FAILED);
	(*line)->lprompt = ft_strlen((*line)->prompt);
	(*line)->curr->quoted = 1;
	put_prompt((*line)->prompt);
	(*line)->tmp[0] = 0;
	while ((*line)->tmp[0] == 0 || ((*line)->tmp[0] == 4))
		deal_typing(*line);
	write(1, "\n", 1);
	(*line)->curr->quoted = 0;
	ft_strdel(&(*line)->prompt);
	(*line)->prompt = promptsave;
	(*line)->lprompt = ft_strlen((*line)->prompt);
	if ((*line)->tmp[0] == -1)
		return (ERR_FREE_ALL);
	return (ERR_NONE);
}

static int		old_input_type(t_token *token, t_line *line, t_p_param *param,
t_n_input *input)
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
			if (!(*param->line = ft_strjoin(input->linesave, ";")))
				return (ERR_MALLOC_FAILED);
	}
	else if (input->type == BACKQUOTE)
	{
		if (*line->curr->buff
		&& token->head[token->len - 1] != '`'
		&& line->curr->buff[0] != '`')
			if (!(*param->line = ft_strjoin(input->linesave, ";")))
				return (ERR_MALLOC_FAILED);
	}
	else if (!(*param->line = ft_strjoin(input->linesave, "\n")))
		return (ERR_MALLOC_FAILED);
	return (ERR_NONE);
}

int				parse_new_input(t_token **token, t_p_param *param, t_s_env *e)
{
	t_n_input	input;
	t_line		*line;
	t_token		*newt;

	input.type = quote_type((*token)->quote);
	if ((input.error = get_new_input(*token, &line)) != ERR_NONE)
		return (input.error);
	input.linesave = *param->line;
	*param->line = NULL;
	if (old_input_type(*token, line, param, &input))
		return (ERR_MALLOC_FAILED);
	if (!(*param->line = (*param->line != NULL) ?
		ft_strjoinfree(*param->line, line->curr->buff, 1) :
		ft_strjoin(input.linesave, line->curr->buff)))
		return (ERR_MALLOC_FAILED);
	newt = get_token(*token, param->line, input.linesave, e);
	if (!(*token)->prev)
		*param->token = newt;
	free_token(token);
	return ((*token = newt) ? ERR_NONE : ERR_FREE_ALL);
}
