/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:13:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/13 18:00:30 by gbourgeo         ###   ########.fr       */
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
	if (!(ret = tokenise(*line + ft_strlen(oldl) - token->len, e)))
		return (NULLTOKEN);
	ft_strdel(&oldl);
	ret->prev = token->prev;
	if (ret->prev)
		ret->prev->next = ret;
	return (ret);
}

static t_line	*get_new_input(t_token *token)
{
	t_line		*line;
	char		*promptsave;

	// line->param = param;
	if (!(line = get_struct()))
		return (NULL);
	promptsave = line->prompt;
	init_new_buff(line);
	if (!(line->prompt = get_prompt(token->quote)))
		return (NULL);
	line->lprompt = ft_strlen(line->prompt);
	put_prompt(line->prompt);
	deal_typing(line);
	////// Handle CTRL-C + CTRL-D !!
	ft_strdel(&line->prompt);
	line->prompt = promptsave;
	line->lprompt = ft_strlen(line->prompt);
	return (line);
}

static int		old_input_type(t_token *token, t_line *line, t_p_param *param, int type, char *l)
{
	if (type == BACKSLASH)
		l[ft_strlen(l) - 1] = '\0';
	else if (type == PARENTHESE)
	{
		if (*line->curr->buff
		&& ft_strncmp(token->head + token->len - 2, "$(", 2)
		&& line->curr->buff[0] != ')')
			if (!(*param->line = ft_strjoin(l, ";")))
				return (ERR_MALLOC_FAILED);
	}
	else if (type == BACKQUOTE)
	{
		if (*line->curr->buff
		&& token->head[token->len - 1] != '`'
		&& line->curr->buff[0] != '`')
			if (!(*param->line = ft_strjoin(l, ";")))
				return (ERR_MALLOC_FAILED);
	}
	else if (!(*param->line = ft_strjoin(l, "\n")))
		return (ERR_MALLOC_FAILED);
	return (ERR_NONE);
}

int				parse_new_input(t_token **token, t_p_param *param, t_s_env *e)
{
	t_line		*line;
	char		*linesave;
	int			type;
	t_token		*newt;

	type = quote_type((*token)->quote);
	if (!(line = get_new_input(*token)))
		return (ERR_MALLOC_FAILED);
	linesave = *param->line;
	*param->line = NULL;
	if (old_input_type(*token, line, param, type, linesave))
		return (ERR_MALLOC_FAILED);
	if (!(*param->line = (*param->line != NULL) ?
		ft_strjoinfree(*param->line, line->curr->buff, 1) :
		ft_strjoin(linesave, line->curr->buff)))
		return (ERR_MALLOC_FAILED);
	if (!(newt = get_token(*token, param->line, linesave, e)))
		return (ERR_TOKENIZATION);
	free_token(token);
	*token = newt;
	return (ERR_NONE);
}
