/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 22:38:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/31 18:13:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "expansion.h"
#include "expansion_errors.h"

static int		token_end(t_exp *param)
{
	return (param->i < param->buff_len);
}

int				expand_argument(t_argument *arg, t_s_env *e)
{
	t_exp		param;
	t_ret		ret;
	int			error;

	if (!arg || !arg->token)
		return (0);
	ft_memset(&param, 0, sizeof(param));
	ft_memset(&ret, 0, sizeof(ret));
	param.e = e;
	param.buff = arg->token->head;
	param.buff_len = arg->token->len;
	param.expand = 1;
	param.fieldsplit = (arg->token->id != ASSIGNMENT_WORD);
	if ((error = expand_loop(&ret, &param, token_end)) != ERR_NONE)
		return (expand_error(error, e->progname, &ret));
	if (expand_end(&ret, arg))
		return (expand_error(ERR_MALLOC, e->progname, &ret));
	if (arg->token && arg->token->prev && arg->token->prev->type == OPERATOR
		&& sh_tablen((const char **)arg->cmd) > 1)
		return (expand_error(ERR_AMBIGUOUS, e->progname, &ret));
	expand_free_t_ret(&ret, 0);
	return (expand_argument(arg->next, e));
}
