/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 22:38:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 19:16:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

static size_t	table_len(char **table)
{
	size_t		i;

	i = 0;
	if (table)
		while (table[i])
			i++;
	return (i);
}

static int		token_end(t_exp *param)
{
	return (param->i < param->buff_len);
}

int				expand_argument(const char *buff, t_argument *arg, t_s_env *e)
{
	t_exp		param;
	t_ret		*ret;
	int			error;

	if (!arg || !arg->token)
		return (0);
	ft_memset(&param, 0, sizeof(param));
	if (!(ret = ft_memalloc(sizeof(*ret))))
		return (expand_error(ERR_MALLOC, e->progname, ret));
	param.e = e;
	param.buff = buff + arg->token->head;
	param.buff_len = arg->token->tail - arg->token->head;
	param.expand = 1;
	param.fieldsplit = (arg->token->id != ASSIGNMENT_WORD);
	if ((error = expand_loop(ret, &param, token_end)) != ERR_NONE)
		return (expand_error(error, e->progname, ret));
	if (expand_end(ret, arg))
		return (expand_error(ERR_MALLOC, e->progname, ret));
	if (arg->token && arg->token->prev && arg->token->prev->type == OPERATOR
		&& table_len(arg->cmd) > 1)
		return (expand_error(ERR_AMBIGUOUS, e->progname, ret));
	free_t_ret(&ret);
	return (expand_argument(buff, arg->next, e));
}
