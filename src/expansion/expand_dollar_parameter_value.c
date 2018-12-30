/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter_value.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 04:42:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 16:53:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

static char		*getnenv(const char *name, char **env)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = (name) ? ft_strlen(name) : 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (exp_strncmp(env[i], name, len) == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

static int		spec_error(int error, char *save)
{
	free(save);
	return (error);
}

int				expand_dollar_parameter_value(t_ret *parameter, t_exp *param)
{
	t_ret		substitute;
	char		*word;

	ft_memset(&substitute, 0, sizeof(substitute));
	word = &parameter->word[parameter->brace + parameter->hash + 1];
	if (!*word)
		return (ERR_NONE);
	if (is_valid_name(word[0]))
	{
		if (!(substitute.word = getnenv(word, param->e->public_env)))
			substitute.word = getnenv(word, param->e->private_env);
	}
	else if (ft_isdigit(word[0]))
	{
		int		nb = ft_atoi(word);

		substitute.word = (nb < param->e->ac) ? param->e->av[nb] : NULL;
	}
	else if (is_special(word[0]))
	{
		if (word[0] == '@')
		{
			size_t	j = 1;
			while (param->e->av[j])
			{
				if (param_addchar('"', &substitute)
					|| param_addstr(param->e->av[j], &substitute)
					|| param_addchar('"', &substitute)
					|| (param->e->av[j + 1]
						&& param_addchar(' ', &substitute)))
					return (spec_error(ERR_MALLOC, substitute.word));
				j++;
			}
			parameter->freeable = 1;
		}
		else if (word[0] == '*')
		{
			size_t	j = 1;
			if (param_addchar('"', &substitute))
				return (spec_error(ERR_MALLOC, substitute.word));
			while (param->e->av[j])
			{
				if (param_addstr(param->e->av[j], &substitute)
					|| (param->e->av[j + 1]
						&& param_addchar(' ', &substitute)))
					return (spec_error(ERR_MALLOC, substitute.word));
				j++;
			}
			if (param_addchar('"', &substitute))
				return (spec_error(ERR_MALLOC, substitute.word));
			parameter->freeable = 1;
		}
		else if (word[0] == '#')
		{
			char	*nbr = ft_itoa(param->e->ac - 1);
			int		error;

			error = param_addstr(nbr, &substitute);
			if (nbr)
				free(nbr);
			if (error)
				return (spec_error(error, substitute.word));
			parameter->freeable = 1;
		}
		else if (word[0] == '?')
		{
			char	*nbr = ft_itoa(param->e->ret);
			int		error;

			error = param_addstr(nbr, &substitute);
			if (nbr)
				free(nbr);
			if (error)
				return (spec_error(error, substitute.word));
			parameter->freeable = 1;
		}
		else if (word[0] == '-')
		{
			/* 21sh options ... */
		}
		else if (word[0] == '$')
		{
			char	*nbr = ft_itoa(getpid());
			int		error;

			error = param_addstr(nbr, &substitute);
			if (nbr)
				free(nbr);
			if (error)
				return (spec_error(error, substitute.word));
			parameter->freeable = 1;
		}
		else if (word[0] == '!')
		{
			/* job control pid list */
		}
	}
	else
		return (spec_error(ERR_SYNTAX, substitute.word));
	parameter->substitute = substitute.word;
	return (ERR_NONE);
}
