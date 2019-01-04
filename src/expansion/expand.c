/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:18:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/03 20:08:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

static int		token_end(t_exp *param)
{
	return (param->i < param->buff_len);
}

static int		expand_argument(const char *buff, t_argument *arg, t_s_env *e)
{
	t_exp		param;
	t_ret		ret;
	int			error;

	if (!arg || !arg->token)
		return (ERR_NONE);
	ft_memset(&param, 0, sizeof(param));
	ft_memset(&ret, 0, sizeof(ret));
	param.ifs = SEPARATORS;
	param.e = e;
	param.buff = buff + arg->token->head;
	param.buff_len = arg->token->tail - arg->token->head;
	if ((error = expand_parameter(&ret, &param, token_end)) != ERR_NONE)
		return (expand_error(error, e->progname, ret.word));
	ft_putendl(ret.word);///////////////////////////////////////////////////////
	return (expand_argument(buff, arg->next, e));
}

static int		check_type(const char *buff, void *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (expand_argument(buff, ((t_command *)cmd)->args, e))
		return (1);
	if (*(int *)cmd == IS_A_PIPE)
		return (check_type(buff, ((t_pipeline *)cmd)->right, e));
	else if (((t_command *)cmd)->redir)
		return (expand_argument(buff, ((t_command *)cmd)->redir->arg, e));
	return (0);
}

int				expand(const char *buff, t_m_list *list, t_s_env *e)
{
	if (!list)
		return (ERR_NONE);
	if (list->aolist)
		if (check_type(buff, list->aolist->cmd, e))
			return (1);
	return (expand(buff, list->next, e));
}
