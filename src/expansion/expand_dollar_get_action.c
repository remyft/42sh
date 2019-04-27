/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_get_action.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 06:50:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/27 17:17:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_action.h"
#include "expansion_errors.h"
#include "expansion_dollar.h"

static int		action_percent(t_ret *parameter, int value)
{
	++parameter->i;
	parameter->action = REMOVE_SMALLEST_SUFFIX_PATTERN;
	value = parameter->head[parameter->brace + parameter->hash + parameter->i];
	if (value == '%')
	{
		parameter->action = REMOVE_LARGEST_SUFFIX_PATTERN;
		++parameter->i;
	}
	return (ERR_NONE);
}

static int		action_hash(t_ret *parameter, int value)
{
	++parameter->i;
	parameter->action = REMOVE_SMALLEST_PREFIX_PATTERN;
	value = parameter->head[parameter->brace + parameter->hash + parameter->i];
	if (value == '#')
	{
		parameter->action = REMOVE_LARGEST_PREFIX_PATTERN;
		++parameter->i;
	}
	return (ERR_NONE);
}

static int		action_values(t_ret *parameter, int value)
{
	if (value == '-')
		parameter->action |= ACT_NULL_SUBST;
	else if (value == '=')
		parameter->action |= ACT_NULL_ASSIGN;
	else if (value == '?')
		parameter->action |= ACT_NULL_ERROR;
	else if (value == '+')
		parameter->action |= ACT_NONNULL_SUBST;
	++parameter->i;
	return (ERR_NONE);
}

static int		action_colon(t_ret *parameter, int value)
{
	++parameter->i;
	parameter->action = COLON_ACTION;
	value = parameter->head[parameter->brace + parameter->hash + parameter->i];
	if (ft_strchr("-=?+", value))
		return (action_values(parameter, value));
	return (ERR_MODIFIER);
}

int				expand_dollar_get_action(t_ret *parameter)
{
	static t_action	action[] = {
		{ ":", action_colon }, { "-=?+", action_values },
		{ "#", action_hash }, { "%", action_percent },
	};
	size_t			i;
	int				value;

	i = 0;
	value = parameter->head[++parameter->i];
	if (!parameter->brace
	|| is_expand_null(parameter)
	|| value == '}')
		return (ERR_NONE);
	while (i < sizeof(action) / sizeof(action[0]))
	{
		if (ft_strchr(action[i].value, value))
			return (action[i].handler(parameter, value));
		i++;
	}
	return (ERR_NONE);
}
