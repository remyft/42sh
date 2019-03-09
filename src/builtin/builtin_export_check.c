/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:35:33 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/09 19:09:53 by tsisadag         ###   ########.fr       */
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
	int		i;

	i = 0;
	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	while (private_env[i])
	{
		if (ft_strncmp(private_env[i], tmp, len) == '=' ||
			ft_strncmp(private_env[i], tmp, len) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int		is_public(char *var, char **public_env)
{
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	while (public_env[i])
	{
		if (ft_strncmp(public_env[i], tmp, len) == '=' ||
			ft_strncmp(public_env[i], tmp, len) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int		is_exported(char *var, char **exported_env)
{
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	while (exported_env[i])
	{
		if (ft_strncmp(exported_env[i], tmp, len) == '=' ||
			ft_strncmp(exported_env[i], tmp, len) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int		var_name_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}
