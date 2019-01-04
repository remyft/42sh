/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 02:35:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 03:05:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_tilde.h"
#include "expansion_errors.h"

static int		tilde_end(t_exp *param)
{
	return (param->buff[param->i] != '/' || param->quoted);
}

static int		tilde_get_parameter(t_ret *parameter, t_exp *param)
{
	int			error;

	error = ERR_NONE;
	ft_memset(parameter, 0, sizeof(*parameter));
	param_addchar('~', parameter);
	param->i++;
	if ((error = expand_parameter(parameter, param, tilde_end)) != ERR_NONE)
		return (error);
	parameter->word = ft_strcpy(parameter->word, parameter->word + 1);
	parameter->w_len--;
	param->i--;
//	debug_expansion("tilde", parameter);
	return (error);
}

int				expand_tilde(t_exp *param, t_ret *ret)
{
	static t_tilde	tilde[] = {
		TILDE_NONE, TILDE_PLUS, TILDE_MINUS, TILDE_DIGIT, TILDE_ALPHA,
	};
	size_t			i;
	t_ret			parameter;
	int				error;

	i = 0;
	if (ret->w_len != 0)
		return (param_addchar('~', ret));
	if ((error = tilde_get_parameter(&parameter, param)) != ERR_NONE)
		return (error);
	while (i < sizeof(tilde) / sizeof(tilde[0]))
	{
		if (tilde[i].comparaison(parameter.word))
			return (tilde[i].handler(ret, parameter.word, param));
		i++;
	}
	return (expand_tilde_not(ret, parameter.word));
}

int				expand_tilde_not(t_ret *ret, const char *word)
{
	if (param_addchar('~', ret) || param_addstr(word, ret))
		return (ERR_MALLOC);
	return (ERR_NONE);
}
