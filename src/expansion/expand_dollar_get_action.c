/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_get_action.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 06:50:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/28 18:49:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_action.h"

static int		get_action(int c)
{
	if (c == '-')
		return (ACT_NULL_SUBST);
	if (c == '=')
		return (ACT_NULL_ASSIGN);
	if (c == '?')
		return (ACT_NULL_ERROR);
	if (c == '+')
		return (ACT_NONNULL_SUBST);
	return (NO_ACTION);
}

int				expand_dollar_get_action(t_ret *parameter, t_exp *param)
{
	parameter->action = NO_ACTION;
	if (!parameter->brace
		|| is_expand_null(parameter)
		|| param->buff[param->i] == '}')
		return (ERR_NONE);
	else if (param->buff[param->i] == ':')
	{
		parameter->action |= COLON_ACTION;
		++param->i;
		if (ft_strchr(ACTIONS_VALUES, param->buff[param->i]))
		{
			parameter->action |= get_action(param->buff[param->i]);
			++param->i;
		}
		else
			return (ERR_MODIFIER);
	}
	else if (param->buff[param->i] == '#')
	{
		parameter->action = REMOVE_SMALLEST_PREFIX_PATTERN;
		++param->i;
		if (param->buff[param->i] == '#')
		{
			parameter->action = REMOVE_LARGEST_PREFIX_PATTERN;
			++param->i;
		}
	}
	else if (param->buff[param->i] == '%')
	{
		parameter->action = REMOVE_SMALLEST_SUFFIX_PATTERN;
		++param->i;
		if (param->buff[param->i] == '%')
		{
			parameter->action = REMOVE_LARGEST_SUFFIX_PATTERN;
			++param->i;
		}
	}
	else if (ft_strchr(ACTIONS_VALUES, param->buff[param->i]))
	{
		parameter->action = get_action(param->buff[param->i]);
		++param->i;
	}
	else
		return (ERR_SYNTAX);
	return (ERR_NONE);
}