/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 04:44:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/26 11:04:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_parameter.h"

// static int		exp_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	char		*p1;
// 	char		*p2;

// 	p1 = (char *)s1;
// 	p2 = (char *)s2;
// 	while (*p1 && *p2 && n--)
// 		if (*p1++ != *p2++)
// 			break ;
// 	return (*p1 - *p2);
// }

// static char		*getnenv(const char *name, size_t len, char **env)
// {
// 	size_t		i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (exp_strncmp(env[i], name, len) == '=')
// 			return (&env[i][len + 1]);
// 	}
// 	return (NULL);
// }

static int		dollar_valid_name(int c)
{
	return ((c == '_') || ft_isalnum(c));
}

static int		dollar_special(int c)
{
	return ((c == '@')
		|| (c == '*')
		|| (c == '#')
		|| (c == '?')
		|| (c == '-')
		|| (c == '$')
		|| (c == '!'));
}

static int		dollar_end(t_exp *param)
{
	return (dollar_valid_name(param->buff[param->i])
		|| dollar_special(param->buff[param->i]));
}

int				expand_dollar_parameter(t_exp *param, t_ret *ret)
{
	t_ret		word;
	t_exp_p		eparam;

	ft_memset(&word, 0, sizeof(word));
	ft_memset(&eparam, 0, sizeof(eparam));
	if ((eparam.brace = param->buff[param->i] == '{'))
		++param->i;
	if ((eparam.hash = param->buff[param->i] == '#'))
	{
		// if (!eparam.brace)
		// 	return (expand_substitution(param, &word, ret));
		++param->i;
	}
	expand_mword(&word, param, dollar_end);
	if (eparam.brace)
		expand_dollar_brace(&word, param);
	size_t		i = 0;
	if (!word.word)
		return (param_addchar(param->buff[--param->i], ret));
	else if (dollar_valid_name(word.word[i]))
	{
		while (dollar_valid_name(param->buff[param->i]))
		{
			if (param_addchar(param->buff[param->i], &word))
				return (ERR_MALLOC);
			++param->i;
		}
	}
	else if (ft_isdigit(param->buff[param->i]))
	{
		eparam.special = 1;
		while (ft_isdigit(param->buff[param->i]))
		{
			if (param_addchar(param->buff[param->i], &word))
				return (ERR_MALLOC);
			++param->i;
		}
	}
	else if (dollar_special(param->buff[param->i]))
	{
		eparam.special = 1;
		if (param_addchar(param->buff[param->i], &word))
			return (ERR_MALLOC);
		++param->i;
		// if (param->buff[param->i] == '@')
		// {
		// 	size_t	j = 1;
		// 	while (param->e->av[j])
		// 	{
		// 		if ((param->error = param_addchar('"', ret))
		// 			|| (param->error = param_addstr(param->e->av[j], ret))
		// 			|| (param->error = param_addchar('"', ret))
		// 			|| (param->e->av[j + 1]
		// 				&& (param->error = param_addchar(' ', ret))))
		// 			return ;
		// 		j++;
		// 	}
		// }
		// else if (param->buff[i] == '*')
		// {
		// 	size_t	j = 1;
		// 	if ((param->error = param_addchar('"', ret)))
		// 		return ;
		// 	while (param->e->av[j])
		// 	{
		// 		if ((param->error = param_addstr(param->e->av[j], ret))
		// 			|| (param->e->av[j + 1]
		// 				&& (param->error = param_addchar(' ', ret))))
		// 			return ;
		// 		j++;
		// 	}
		// 	if ((param->error = param_addchar('"', ret)))
		// 		return ;
		// }
		// else if (param->buff[i] == '#')
		// {
		// 	char	*nbr = ft_itoa(param->e->ac - 1);

		// 	param->error = param_addstr(nbr, ret);
		// 	if (nbr)
		// 		free(nbr);
		// }
		// else if (param->buff[i] == '?')
		// {
		// 	char	*nbr = ft_itoa(param->e->ret);

		// 	param->error = param_addstr(nbr, ret);
		// 	if (nbr)
		// 		free(nbr);
		// }
		// else if (param->buff[i] == '-')
		// {
		// 	/* 21sh options ... */
		// }
		// else if (param->buff[i] == '$')
		// {
		// 	char	*nbr = ft_itoa(param->e->pid);

		// 	param->error = param_addstr(nbr, ret);
		// 	if (nbr)
		// 		free(nbr);
		// }
		// else if (param->buff[i] == '!')
		// {
		// 	/* job control pid list */
		// }
		// param->i = i;
	}
	else if (eparam.brace)
		return (ERR_SYNTAX);
	if (eparam.brace)
		expand_brace(param, &word);
	param_addstr(word.word, ret);
	// expand_substitution(param, &word, ret);
	--param->i;
	return (ERR_NONE);
}