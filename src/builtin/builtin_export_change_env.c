/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_change_env.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 18:08:03 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/25 23:34:29 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"

void	delete_local(char *arg, t_s_env ****e, int i, int j)
{
	char	**clone;
	char	*tmp1;
	char	*tmp2;

	clone = ft_memalloc(sizeof(char **) *
			(count_strarr((***e)->private_env)));
	tmp1 = ft_strsub(arg, 0, var_name_len(arg));
	while ((***e)->private_env[i])
	{
		tmp2 = ft_strsub((***e)->private_env[i], 0,
				var_name_len((***e)->private_env[i]));
		(ft_strcmp(tmp1, tmp2) == 0) ? i++ : i;
		if (!((***e)->private_env[i]))
		{
			free(tmp2);
			break ;
		}
		clone[j++] = ft_strdup((***e)->private_env[i++]);
		free(tmp2);
	}
	free(tmp1);
	clone[j] = NULL;
	sh_freetab(&(***e)->private_env);
	(***e)->private_env = clone_arr(clone);
	sh_freetab(&clone);
}

void	delete_exported(char *arg, t_s_env ****e, int i, int j)
{
	char	**clone;
	char	*tmp1;
	char	*tmp2;

	clone = ft_memalloc(sizeof(char **) * (count_strarr((***e)->exported_env)));
	tmp1 = ft_strsub(arg, 0, var_name_len(arg));
	while ((***e)->exported_env[i])
	{
		tmp2 = ft_strsub((***e)->exported_env[i], 0,
				var_name_len((***e)->exported_env[i]));
		(ft_strcmp(tmp1, tmp2) == 0) ? i++ : i;
		if (!((***e)->exported_env[i]))
		{
			free(tmp2);
			break ;
		}
		clone[j++] = ft_strdup((***e)->exported_env[i++]);
		free(tmp2);
	}
	free(tmp1);
	clone[j] = NULL;
	sh_freetab(&(***e)->exported_env);
	(***e)->exported_env = clone_arr(clone);
	sh_freetab(&clone);
}

void	add_public(char *arg, t_s_env ****e)
{
	char	**clone;
	char	*tmp;
	int		i;

	i = 0;
	clone = ft_memalloc(sizeof(char **) *
			(count_strarr((***e)->public_env) + 2));
	while ((***e)->public_env[i])
	{
		clone[i] = ft_strdup((***e)->public_env[i]);
		i++;
	}
	tmp = (!has_value(arg)) ? ft_strjoin(arg, "=") : ft_strdup(arg);
	clone[i] = (sh_getnenv(arg, (***e)->private_env)) ? ft_strjoin(tmp,
				sh_getnenv(arg, (***e)->private_env)) : ft_strdup(tmp);
	free(tmp);
	clone[++i] = NULL;
	sh_freetab(&(***e)->public_env);
	(***e)->public_env = clone_arr(clone);
	sh_freetab(&clone);
}

void	add_exported(char *arg, t_s_env ***e)
{
	char	**clone;
	int		i;

	i = 0;
	clone = ft_memalloc(sizeof(char **) *
			(count_strarr((**e)->exported_env) + 2));
	while ((**e)->exported_env[i])
	{
		clone[i] = ft_strdup((**e)->exported_env[i]);
		i++;
	}
	clone[i++] = ft_strdup(arg);
	clone[i] = NULL;
	sh_freetab(&(**e)->exported_env);
	(**e)->exported_env = clone_arr(clone);
	sh_freetab(&clone);
}

void	change_public(char *arg, t_s_env ****e)
{
	int		i;
	int		len;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	len = var_name_len(arg);
	while ((***e)->public_env[++i])
	{
		tmp1 = ft_strsub(arg, 0, len);
		tmp2 = ft_strsub((***e)->public_env[i], 0, len);
		if (ft_strcmp(tmp1, tmp2) == 0)
		{
			free((***e)->public_env[i]);
			(***e)->public_env[i] = ft_strdup(arg);
			if (ft_strncmp("PATH", arg, 4) == 0 && arg[4] == '=')
				check_path(***e);
			free(tmp1);
			free(tmp2);
			return ;
		}
		free(tmp1);
		free(tmp2);
	}
	printf("errror\n");
}
