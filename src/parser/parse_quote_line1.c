/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_line1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:16:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/06 18:57:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_errors.h"

int				aliased_line(t_token *token, t_line *line, t_n_input *input)
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

int				bslashed_line(t_token *token, t_line *line, t_n_input *input)
{
	(void)line;
	input->linesave[ft_strlen(input->linesave) - 1] = '\0';
	token->len--;
	return (ERR_NONE);
}

int				dquoted_line(t_token *token, t_line *line, t_n_input *input)
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

int				squoted_line(t_token *token, t_line *line, t_n_input *input)
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

int				braced_line(t_token *token, t_line *line, t_n_input *input)
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
