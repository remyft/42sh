/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:18:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 10:44:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

static int		expand_loop(t_ret *ret, t_exp *param, int (*end_loop)(t_exp *))
{
	int			error;

	error = ERR_NONE;
	if (param->buff[param->i] == '~')
		error = expand_tilde(param, ret);
	while (param->i < param->buff_len && end_loop(param))
	{
		if (param->buff[param->i] == '\'')
			error = expand_squote(param, ret);
		else if (param->buff[param->i] == '"')
			error = expand_dquote(param, ret);
		else if (param->buff[param->i] == '\\')
			error = expand_backslash(param, ret);
		else if (param->buff[param->i] == '$')
			error = expand_dollar(param, ret);
		else if (param->buff[param->i] == '`'
			|| param->buff[param->i] == '(')
			error = expand_backtick(param, ret);
		// else if (param->buff[param->i] == '*'
		// 	|| param->buff[param->i] == '['
		// 	|| param->buff[param->i] == '?')
		// 	error = expand_glob(param, ret);
		else
			error = param_addchar(param->buff[param->i], ret);
		if (error)
			break ;
		param->i++;
	}
	return (error);
}

int				expand_mword(t_ret *ret, t_exp *param, int (*end)(t_exp *))
{
	int			error;

	if ((error = expand_loop(ret, param, end)) != ERR_NONE)
		return (error);
	// fieldsplit(&ret);
	// expand_pathname();
	// remove_quote(&ret);
	return (ERR_NONE);
}

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
	if ((error = expand_mword(&ret, &param, token_end)) != ERR_NONE)
		return (expand_error(error, e->progname, ret.word));
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
