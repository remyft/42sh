/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter_value.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 04:42:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 19:40:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "expansion_is.h"
#include "expansion_dollar.h"
#include "expansion_errors.h"
#include "expansion_special.h"

static int		expand_argv(t_ret *para, t_exp *param)
{
	char		*digits;
	int			nb;

	digits = &para->word[para->brace + para->hash + 1];
	nb = (para->brace) ? ft_atoi(digits) : *digits - '0';
	if (param->e->filein)
		nb++;
	para->substitute = (nb >= 0 && nb < param->e->ac) ? param->e->av[nb] : NULL;
	para->freeable = 0;
	if (para->brace)
		while (ft_isdigit(digits[para->i]))
			para->i++;
	return (ERR_NONE);
}

static int		expand_env(t_ret *para, t_exp *param)
{
	char		*word;
	char		c;

	word = &para->word[para->i];
	if (para->brace)
	{
		while (word[para->i] && is_valid_name(word[para->i]))
			para->i++;
		c = word[para->i];
		word[para->i] = '\0';
	}
	if (!(para->substitute = sh_getnenv(word, param->e->public_env)))
		para->substitute = sh_getnenv(word, param->e->private_env);
	if (para->brace)
		word[para->i] = c;
	para->freeable = 0;
	return (ERR_NONE);
}

int				expand_dollar_parameter_value(t_ret *parameter, t_exp *param)
{
	static t_dollar	dollar[] = {
		{ is_special, expand_dollar_special },
		{ ft_isdigit, expand_argv },
		{ is_valid_name, expand_env },
	};
	size_t			i;
	char			*word;

	i = 0;
	parameter->i = 1 + parameter->brace + parameter->hash;
	word = &parameter->word[parameter->i];
	if (!word[0])
	{
		if (!parameter->hash)
			return (ERR_SYNTAX);
		return (special_argc(parameter, param));
	}
	while (i < sizeof(dollar) / sizeof(dollar[0]))
	{
		if (dollar[i].check(word[0]))
			return (dollar[i].handler(parameter, param));
		i++;
	}
	return (ERR_SYNTAX);
}
