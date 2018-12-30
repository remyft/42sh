/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 09:45:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 19:33:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_action.h"

static char		**getnenvaddr(const char *name, char **env)
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
			return (env + i);
		i++;
	}
	return (NULL);
}

static char		**newenv(char ***env)
{
	char		**save;
	size_t		len;

	save = *env;
	len = 0;
	while (save && save[len])
		len++;
	if (!(*env = ft_memalloc(sizeof(**env) * (len + 2))))
	{
		*env = save;
		return (NULL);
	}
	len = 0;
	while (save && save[len])
	{
		(*env)[len] = save[len];
		len++;
	}
	return (&(*env)[len]);
}

static int		replace_env_value(t_ret *parameter, t_ret *word, t_exp *param)
{
	char		*name;
	char		**ret;
	char		*save;
	size_t		len;

	name = parameter->word + parameter->brace + parameter->hash + 1;
	if (!(ret = getnenvaddr(name, param->e->public_env)))
		if (!(ret = getnenvaddr(name, param->e->private_env)))
			if (!(ret = newenv(&param->e->private_env)))
				return (ERR_MALLOC);
	save = *ret;
	len = ft_strlen(name) + 2;
	len += (word->substitute) ?
		ft_strlen(word->substitute) : ft_strlen(word->word);
	if (!(*ret = ft_memalloc(len)))
	{
		*ret = save;
		return (ERR_MALLOC);
	}
	free(save);
	ft_strcpy(*ret, name);
	ft_strcat(*ret, "=");
	if (word->substitute)
		ft_strcat(*ret, word->substitute);
	else if (word->word)
		ft_strcat(*ret, word->word);
	return (ERR_NONE);
}

int				expand_dollar_word_value(t_ret *parameter, t_exp *param)
{
	t_ret		word;
	int			error;

	ft_memset(&word, 0, sizeof(word));
	error = ERR_NONE;
param->tabval++;
	if (expand_dollar_do_expansion(parameter))
		if ((error = expand_mword(&word, param, is_word_end)) != ERR_NONE)
			return (error);
param->tabval--;
//debug_expansion("word", &word, param);
	if (parameter->action & REMOVE_SMALLEST_SUFFIX_PATTERN
		|| parameter->action & REMOVE_LARGEST_SUFFIX_PATTERN
		|| parameter->action & REMOVE_SMALLEST_PREFIX_PATTERN
		|| parameter->action & REMOVE_LARGEST_PREFIX_PATTERN)
		return (ERR_UNHANDLED_YET);
	if (parameter->action & ACT_NULL_SUBST) /* - */
	{
		if (parameter->substitute && parameter->substitute[0])
			return (ERR_NONE);
		expand_free_t_ret(parameter);
		parameter->word = word.substitute;
		parameter->substitute = word.word;
	}
	else if (parameter->action & ACT_NULL_ASSIGN) /* = */
	{
		if (parameter->substitute && parameter->substitute[0])
			return (ERR_NONE);
		if (replace_env_value(parameter, &word, param) != ERR_NONE)
			return (ERR_MALLOC);
		expand_free_t_ret(parameter);
		parameter->word = word.substitute;
		parameter->substitute = word.word;
	}
	else if (parameter->action & ACT_NULL_ERROR) /* ? */
	{
		if (parameter->substitute && parameter->substitute[0])
			return (ERR_NONE);
		if (!(parameter->action & COLON_ACTION) && parameter->substitute)
			;
		else
		{
			if (param_addstr(": ", parameter))
				return (ERR_MALLOC);
			if (word.substitute && word.substitute[0])
			{
				if (param_addstr(word.substitute, parameter))
					return (ERR_MALLOC);
			}
			else if (word.word && word.word[0])
			{
				if (param_addstr(word.word, parameter))
					return (ERR_MALLOC);
			}
			else if (param_addstr("parameter not set", parameter))
				return (ERR_MALLOC);
			expand_free_t_ret(&word);
			parameter->substitute = parameter->word + parameter->brace
									+ parameter->hash + 1;
			return (ERR_GIVEN);
		}
	}
	else if (parameter->action & ACT_NONNULL_SUBST) /* + */
	{
		if (parameter->substitute
			&& (parameter->substitute[0] || !(parameter->action & COLON_ACTION)))
		{
			expand_free_t_ret(parameter);
			parameter->word = word.substitute;
			parameter->substitute = word.word;
		}
	}
	return (error);
}
