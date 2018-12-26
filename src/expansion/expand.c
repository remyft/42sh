/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:18:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 10:45:10 by gbourgeo         ###   ########.fr       */
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
	while (error == ERR_NONE && end_loop(param))
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
		param->i++;
	}
	return ((error) ? expand_error(error, param->e->progname) : 0);
}

int				expand_mword(t_ret *ret, t_exp *param, int (*end)(t_exp *))
{
	if (expand_loop(ret, param, end))
		return (1);
	// fieldsplit(&ret);
	// expand_pathname();
	// remove_quote(&ret);
	ft_putendl(ret->word);
	return (0);
}

static int		token_end(t_exp *param)
{
	return (param->i < param->buff_len);
}

static int		expand_argument(const char *buff, t_argument *arg, t_s_env *e)
{
	t_exp		param;
	t_ret		ret;

	if (!arg || !arg->token)
		return (ERR_NONE);
	param.ifs = SEPARATORS;
	param.e = e;
	param.buff = buff + arg->token->head;
	param.buff_len = arg->token->tail - arg->token->head;
	param.i = 0;
	ft_memset(&ret, 0, sizeof(ret));
	if (expand_mword(&ret, &param, token_end))
		return (1);
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
