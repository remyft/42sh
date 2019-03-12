/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_new_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:13:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 13:48:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "main_tools.h"
#include "token_error.h"
#include "token.h"
#include "shell.h"

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

static void		new_tokens_head(t_token *token, char *line, char *oldline)
{
	while (token)
	{
		token->head = line + (token->head - oldline);
		token = token->next;
	}
}

static t_line	*init_new_input(char **save, t_param *param)
{
	t_line		*line;
	char		*promptsave;

	// line->param = param;
	if (!(line = get_struct()))
		return (NULL); /// //// ??????
	*save = *param->line;
	*param->line = NULL;
	promptsave = line->prompt;
	if (quote_type(param->quote) == BACKSLASH)
		quote_remove(&param->quote, BACKSLASH);
	init_new_buff(line);
	if (!(line->prompt = get_prompt(param->quote)))
		return (NULL); //// ?????
	line->lprompt = ft_strlen(line->prompt);
	put_prompt(line->prompt);
	deal_typing(line);

	ft_strdel(&line->prompt);
	line->prompt = promptsave;
	line->lprompt = ft_strlen(line->prompt);
	return (line);
}

static t_token		*new_input_type(t_line *line, t_param *param, int type, char *l)
{
	if (type == BACKSLASH)
		l[--param->i] = '\0';
	else if (type == PARENTHESE)
	{
		if (*line->curr->buff
		&& ft_strncmp(param->token->head + param->token->len - 2, "$(", 2)
		&& line->curr->buff[0] != ')')
			if (!((*param->line) = ft_strjoin(l, ";")))
				return (token_error(ERR_MALLOC, param));
	}
	else if (type == BACKQUOTE)
	{
		if (*line->curr->buff
		&& param->token->head[param->token->len - 1] != '`'
		&& line->curr->buff[0] != '`')
			if (!((*param->line) = ft_strjoin(l, ";")))
				return (token_error(ERR_MALLOC, param));
	}
	else if ((type == DOUBLE_QUOTE || type == SINGLE_QUOTE || type == BRACE)
		&& (!(*param->line = ft_strjoin(l, "\n"))))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}


t_token			*handle_new_input(t_param *param)
{
	t_line		*line;
	char		*linesave;
	int			type;

	type = quote_type(param->quote);
	if (!(line = init_new_input(&linesave, param)))
		return (token_error(ERR_MALLOC, param)); /// ???
	if (!(param->token = new_input_type(line, param, type, linesave)))
		return (param->token);
	if (!(*param->line = (*param->line) ?
		ft_strjoinfree(*param->line, line->curr->buff, 1) :
		ft_strjoin(linesave, line->curr->buff)))
		return (token_error(ERR_MALLOC, param));
	--param->i;
	new_tokens_head(param->head, *param->line, linesave);
	ft_strdel(&linesave);
	return (param->token);
}
