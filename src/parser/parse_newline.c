/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_newline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:07:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/23 14:02:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int		parse_strncmp(const char *s1, size_t len1,
								const char *s2, size_t len2)
{
	size_t		i;

	i = 0;
	while (i < len1 && i < len2)
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	return (i == len1 && i == len2);
}

int				parse_newline(t_token **tok, t_p_param *par, t_s_env *e)
{
	const char		*head;

	if (!par->heredoc)
		return (1);
	head = (*tok)->head + 1;
	while (*tok)
	{
		if (parse_strncmp((*tok)->head + 1, (*tok)->len - 1,
							par->heredoc->head, par->heredoc->len))
		{
			par->heredoc->head = head;
			par->heredoc->len = (*tok)->head - head;
			((t_redirection *)par->heredoc->redir)->heredoc = par->heredoc;
			par->heredoc = par->heredoc->next;
			return (1);
		}
		*tok = (*tok)->next;
	}
	return (parse_error(ERR_MISSING_PARAMETER, NULLTOKEN, e));
}
