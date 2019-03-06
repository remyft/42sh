/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:35:33 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/06 21:39:03 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"

int		has_value(char *var)
{
	int i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		is_local(char *var, char **private_env)
{
	if (sh_getnenv(var, private_env))
		return (1);
	return (0);
}

int		is_public(char *var, char **public_env)
{
	if (sh_getnenv(var, public_env))
		return (1);
	return (0);
}

int		count_strarr(char **str_array)
{
	int i;

	i = 0;
	while (str_array[i])
		i++;
	return (i);
}

int		var_name_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (i == (int)ft_strlen(var))
	{
		if (var[i])
			return (-1);
		return (-2);
	}
	return (i);
}
