/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:34:19 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/06 21:43:35 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"

int		exec_export(char *arg, t_s_env **e)
{
	// error handling - wrong identifier
	if (!has_value(arg) && !is_local(arg, (*e)->private_env)
		&& !is_public(arg, (*e)->public_env))
		(*e)->exported_env = add_exported(arg, &(*e)->exported_env);
	else if (!has_value(arg) && is_local(arg, (*e)->private_env)
		&& !is_public(arg, (*e)->public_env))
		(*e)->public_env = add_public(arg, &(e));
/*	else if (!is_local(arg, e->private_env)
		&& is_public(arg, e->public_env));
		change_public(arg, &(*e->public_env));*/
	return (0);
}

char	**add_exported(char *arg, char ***exported)
{
	char	**clone;
	int		i;

	i = 0;
	clone = ft_memalloc(sizeof(char **) * (count_strarr(*exported) + 2));
	while (*(exported[i]))
	{
		clone[i] = ft_strdup(*(exported[i]));
		i++;
	}
	clone[i++] = ft_strdup(arg);
	clone[i] = NULL;
	sh_freetab(exported);
	return (clone);
}

char	**add_public(char *arg, t_s_env ***e)
{
	char	**clone;
	char	*tmp;
	int		i;

	i = 0;
	clone = ft_memalloc(sizeof(char **) *
		(count_strarr((**e)->public_env) + 2));
	while ((**e)->public_env[i])
	{
		clone[i] = ft_strdup((**e)->public_env[i]);
		i++;
	}
	tmp = ft_strjoin(arg, "=");
	clone[i++] = ft_strjoin(tmp, sh_getnenv(arg, (**e)->private_env));
	free(tmp);
	clone[i] = NULL;
	sh_freetab(&(**e)->public_env);
	return (clone);
}
