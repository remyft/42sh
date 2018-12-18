/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/18 18:07:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

t_m_list		*parse_error(const char *buff, t_token *token, t_m_list *lhead)
{
	size_t		i;

	i = token->head;
	ft_putstr_fd("21sh: parse error near `", 2);
	if (token->spec == NEWLINE)
		ft_putstr_fd("\\n", 2);
	else
		write(2, buff + token->head, token->tail - token->head);
	ft_putendl_fd("'", 2);
	free_m_list(&lhead);
	return (NULLLIST);
}
