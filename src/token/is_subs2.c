/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_subs2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 01:43:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/14 14:54:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int		ft_isbracketend(t_param *param)
{
	return (param->buff[param->i] == '}'
		&& param->token->quote == BRACKET
		&& --param->token->depth == 0);
}

int		ft_isparenend(t_param *param)
{
	return (param->buff[param->i] == ')'
		&& param->token->quote == PARENTHESE
		&& --param->token->depth == 0);
}

int		ft_isendl(t_param *param)
{
	return ((param->buff[param->i] == '\n')
		|| (param->buff[param->i] == '\0'));
}

int		ft_isspecial(t_param *param)
{
	return ((param->buff[param->i] == '@')
		|| (param->buff[param->i] == '*')
		|| (param->buff[param->i] == '#')
		|| (param->buff[param->i] == '?')
		|| (param->buff[param->i] == '-')
		|| (param->buff[param->i] == '$')
		|| (param->buff[param->i] == '!')
		|| (param->buff[param->i] == '0'));
}

int		ft_isspecialend(t_param *param)
{
	return ((param->buff[param->i - 1] != '$')
		&& (param->buff[param->i - 2] == '$'));
}