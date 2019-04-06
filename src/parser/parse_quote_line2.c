/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_line2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:34:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/06 18:46:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_errors.h"

int				dbraced_line(t_token *token, t_line *line, t_n_input *input)
{
	(void)line;
	if (token->alen)
	{
		if (!(input->linesave = ft_strjoinfree(input->linesave, " ", 1)))
			return (ERR_MALLOC_FAILED);
	}
	else if (!token->alen)
	{
		if (!(input->linesave = ft_strjoinfree(input->linesave, "\n", 1)))
			return (ERR_MALLOC_FAILED);
	}
	return (ERR_NONE);
}

int				parenthed_line(t_token *token, t_line *line, t_n_input *input)
{
	if (*line->curr->buff
	&& ft_strncmp(token->head + token->len - 1, "(", 1)
	&& line->curr->buff[0] != ')')
		if (!(input->linesave = ft_strjoinfree(input->linesave, ";", 1)))
			return (ERR_MALLOC_FAILED);
	return (ERR_NONE);
}

int				dparenthed_line(t_token *token, t_line *line, t_n_input *input)
{
	if (*line->curr->buff
	&& ft_strncmp(token->head + token->len - 2, "$(", 2)
	&& line->curr->buff[0] != ')')
		if (!(input->linesave = ft_strjoinfree(input->linesave, ";", 1)))
			return (ERR_MALLOC_FAILED);
	return (ERR_NONE);
}

int				backquoted_line(t_token *token, t_line *line, t_n_input *input)
{
	if (*line->curr->buff && token->head[token->len - 1] != '`'
	&& line->curr->buff[0] != '`')
		if (!(input->linesave = ft_strjoinfree(input->linesave, ";", 1)))
			return (ERR_MALLOC_FAILED);
	return (ERR_NONE);
}
