/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:35:33 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/08 21:45:21 by tsisadag         ###   ########.fr       */
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
	int		len;
	char	*tmp;

	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	if (sh_getnenv(tmp, private_env))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int		is_public(char *var, char **public_env)
{
	int		len;
	char	*tmp;

	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	if (sh_getnenv(tmp, public_env))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int		is_exported(char *var, char **exported_env)
{
	int		len;
	char	*tmp;

	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	if (sh_getnenv(tmp, exported_env))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
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
	return (i);
}
