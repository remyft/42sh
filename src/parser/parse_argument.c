/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:44:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/26 18:01:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "interactive_error.h"
#include "parser_errors.h"
#include "parser.h"

static int	non_interactive(int type, t_s_env *e)
{
	return (interactive_error(ERR_NON_INT_SUBST, (char *)&type, e));
}

int			parse_argument(t_token **token, t_p_param *param, t_s_env *e)
{
	int		error;

	while (*token && (*token)->quote)
	{
		if (!e->interactive)
			return (non_interactive((*token)->quote->type, e));
		if ((error = parse_new_input(token, param, e)) != ERR_NONE)
			return (parse_error(error, NULLTOKEN, e));
	}
	if ((*param->arg = ft_memalloc(sizeof(**param->arg))) == NULLARG)
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	(*param->arg)->token = *token;
	param->arg = &(*param->arg)->next;
	return (1);
}
