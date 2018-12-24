/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:42:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/21 22:26:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int				parse_operator(t_token *token, t_p_param *param)
{
	if (*param->redir == NULLREDIR
		&& !(*param->redir = ft_memalloc(sizeof(**param->redir))))
		return (0);
	(*param->redir)->token = token;
	if (token->next == NULL)
		return (0);
	if (!((*param->redir)->arg = ft_memalloc(sizeof(*(*param->redir)->arg))))
		return (0);
	(*param->redir)->arg->token = token->next;
	token = token->next;
	if (token->type != TOKEN
		|| (token->spec != WORD
			&& token->spec != NAME))
		return (0);
	token->spec = 0;
	param->redir = &(*param->redir)->next;
	return (1);
}
