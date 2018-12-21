/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:42:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/20 20:48:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int				parse_operator(t_token *token, t_p_param *param)
{
	if (*param->redir == NULLREDIR
		&& !(*param->redir = ft_memalloc(sizeof(**param->redir))))
		return (1);
	(*param->redir)->token = token;
	(*param->redir)->arg = token->next;
	if (token->next == NULL)
		return (1);
	token = token->next;
	if (token->type != TOKEN
		|| (token->spec != WORD
			&& token->spec != NAME))
		return (1);
	token->spec = 0;
	param->redir = &(*param->redir)->next;
	return (0);
}
