/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_special1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 23:02:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 01:10:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_special.h"
#include "expansion_errors.h"

int				expand_dollar_special(t_ret *sub, t_ret *para, t_exp *param)
{
	static t_special	special[] = {
		{ '@', special_argv }, { '*', special_argvs }, { '#', special_argc },
		{ '?', special_return }, { '-', special_option }, { '$', special_pid },
		{ '!', special_jobs },
	};
	size_t				i;
	char				*word;

	i = 0;
	word = &para->word[para->brace + para->hash + 1];
	while (i < sizeof(special) / sizeof(special[0]))
	{
		if (word[0] == special[i].value)
			return (special[i].handler(sub, para, param));
		i++;
	}
	return (ERR_NONE);
}

int				special_error(int error, char *save)
{
	free(save);
	return (error);
}

int				special_argv(t_ret *subs, t_ret *para, t_exp *param)
{
	size_t	j;

	j = 1;
	while (param->e->av[j])
	{
		if (param_addchar('"', subs)
			|| param_addstr(param->e->av[j], subs)
			|| param_addchar('"', subs)
			|| (param->e->av[j + 1]
				&& param_addchar(' ', subs)))
			return (special_error(ERR_MALLOC, subs->word));
		j++;
	}
	para->freeable = 1;
	para->substitute = subs->word;
	return (ERR_NONE);
}

int				special_argvs(t_ret *subs, t_ret *para, t_exp *param)
{
	size_t	j;

	j = 1;
	if (param_addchar('"', subs))
		return (special_error(ERR_MALLOC, subs->word));
	while (param->e->av[j])
	{
		if (param_addstr(param->e->av[j], subs)
			|| (param->e->av[j + 1]
				&& param_addchar(' ', subs)))
			return (special_error(ERR_MALLOC, subs->word));
		j++;
	}
	if (param_addchar('"', subs))
		return (special_error(ERR_MALLOC, subs->word));
	para->freeable = 1;
	para->substitute = subs->word;
	return (ERR_NONE);
}

int				special_argc(t_ret *subs, t_ret *para, t_exp *param)
{
	char	*nbr;
	int		error;

	nbr = ft_itoa(param->e->ac - 1);
	error = param_addstr(nbr, subs);
	if (nbr)
		free(nbr);
	if (error)
		return (special_error(error, subs->word));
	para->freeable = 1;
	para->substitute = subs->word;
	return (ERR_NONE);
}
