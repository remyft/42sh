/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_brace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 05:35:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 11:02:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_action.h"

int				expand_brace(t_ret *parameter, t_exp *param)
{
	t_ret		word;
	int			action;

	ft_memset(&word, 0, sizeof(word));
	action = 0;
	(void)parameter;
	if (param->buff[param->i] == '}')
		return (ERR_NONE);
	else if (param->buff[param->i] == ':')
	{
		action |= COLON_ACTION;
		if (!ft_strchr(ACTIONS_VALUES, param->buff[param->i + 1]))
			return (ERR_SYNTAX);
		else
			action = param->buff[param->i];
	}
	else if (param->buff[param->i] == '#')
	{
		action = REMOVE_SMALLEST_PREFIX_PATTERN;
		if (param->buff[param->i + 1] == '#')
		{
			action = REMOVE_LARGEST_PREFIX_PATTERN;
			++param->i;
		}
	}
	else if (param->buff[param->i] == '%')
	{
		action = REMOVE_SMALLEST_SUFFIX_PATTERN;
		if (param->buff[param->i + 1] == '%')
		{
			action = REMOVE_LARGEST_SUFFIX_PATTERN;
			++param->i;
		}
	}
	return (ERR_NONE);
}