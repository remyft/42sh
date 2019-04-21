/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 23:38:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/21 20:57:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"
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

static int		get_new_line(void *quote, t_line *line)
{
	char		*promptsave;

	promptsave = line->prompt;
	init_new_buff(line);
	if (!(line->prompt = get_new_prompt((t_quote *)quote)))
		return (ERR_MALLOC);
	line->lprompt = ft_strlen(line->prompt);
	line->curr->quoted = 1;
	line->tmp[0] = 0;
	put_prompt(line->prompt, *line->ret);
	while (line->shell_loop && line->tmp[0] == 0)
		deal_typing(line);
	if (line->tmp[0] != 4)
		write(STDIN_FILENO, "\n", 1);
	line->shell_loop = 1;
	line->curr->quoted = 0;
	ft_strdel(&line->prompt);
	line->prompt = promptsave;
	line->lprompt = ft_strlen(line->prompt);
	if (line->tmp[0] == -1)
		return (ERR_FREE_ALL);
	if (line->tmp[0] == 4)
		return (ERR_EOF);
	return (ERR_NONE);
}

static int		tokenise_quote(t_param *param, void *quote, t_line *line)
{
	static int	(*handler[])(t_param *, t_line *) = {
		aliased_line, bslashed_line, dquoted_line, squoted_line, braced_line,
		dbraced_line, parenthed_line, dparenthed_line, backquoted_line,
		heredoc_line,
	};
	char		*old;
	int			error;

	old = (char *)param->line;
	if ((error = handler[quote_type((t_quote *)quote)](param, line)))
		return (error);
	if (!(param->line = ft_strjoinfree(old, (char *)param->line, 3)))
		return (ERR_MALLOC);
	if ((param->token = param->head))
		while (param->token)
		{
			if (param->token->alias)
				param->token->alias = param->line + (param->token->alias - old);
			else
				param->token->head = param->line + (param->token->head - old);
			if (!param->token->next)
				break ;
			param->token = param->token->next;
		}
	return (ERR_NONE);
}

t_token			*quote_line(t_param *param)
{
	t_line		*line;
	int			error;

	line = get_struct();
	if (quote_type(param->token->quote) != NO_QUOTE)
	{
		if ((error = get_new_line(param->token->quote, line)) != ERR_NONE
		|| (error = tokenise_quote(param, param->token->quote, line)) != ERR_NONE)
			return (token_error(error, param));
	}
	else
	{
		if ((error = get_new_line(param->hdoc, line)) != ERR_NONE
		|| (error = tokenise_quote(param, param->hdoc, line)) != ERR_NONE)
			return (token_error(error, param));
	}
	return (param->token);
}
