/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_line_handlers1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:16:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/22 01:47:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"

int				aliased_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = "";
	if (param->token->alias)
		add = " ";
	else if (!param->token->alias)
		add = "\n";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				bslashed_line(t_param *param, t_line *line)
{
	((char *)param->line)[ft_strlen(param->line) - 1] = '\0';
	if ((param->token->alias && --param->token->alen <= 0)
	|| (!param->token->alias && --param->token->len <= 0))
		param->token->type = UNDEFINED;
	param->i -= 2;
	quote_remove(&param->token->quote, BACKSLASH);
	if (!(param->line = ft_strjoinfree(param->line, line->curr->buff, 1)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				dquoted_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = "";
	if (param->token->alias)
		add = " ";
	else if (!param->token->alias)
		add = "\n";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				squoted_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = "";
	if (param->token->alias)
		add = " ";
	else if (!param->token->alias)
		add = "\n";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				braced_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = "";
	if (param->token->alias)
		add = " ";
	else if (!param->token->alias)
		add = "\n";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}
