/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:34:19 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/08 21:57:40 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"

int		exec_export(char *arg, t_s_env **e)
{
	// error handling - wrong identifier
	//adding local should check if its in exported
	//adding public should check if its exported	
	if (!is_local(arg, (*e)->private_env) && !is_public(arg, (*e)->public_env) &&
		(!has_value(arg)))
	{
		if (!is_exported(arg, (*e)->exported_env))
			add_exported(arg, &(e));
	}
	else
		change_public_env(arg, &(e));
	return (0);
}

void	delete_local(char *arg, t_s_env ****e, int i, int j)
{
	char	**clone;
	char	*tmp1;
	char	*tmp2;

	clone = ft_memalloc(sizeof(char **) * (count_strarr((***e)->private_env)));
	tmp1 = ft_strsub(arg, 0, var_name_len(arg));
	while ((***e)->private_env[i])
	{
		tmp2 = ft_strsub((***e)->private_env[i], 0, var_name_len((***e)->private_env[i]));
		if (ft_strcmp(tmp1, tmp2) == 0)
			i++;
		clone[j] = ft_strdup((***e)->private_env[i]);
		j++;
		i++;
		free(tmp2);
	}
	free(tmp1);
	clone[j] = NULL;
	sh_freetab(&(***e)->private_env);
	(***e)->private_env = clone_arr(clone);
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
		tmp2 = ft_strsub((***e)->exported_env[i], 0, var_name_len((***e)->exported_env[i]));
		if (ft_strcmp(tmp1, tmp2) == 0)
			i++;
		clone[j] = ft_strdup((***e)->exported_env[i]);
		j++;
		i++;
		free(tmp2);
	}
	free(tmp1);
	clone[j] = NULL;
	sh_freetab(&(***e)->exported_env);
	(***e)->exported_env = clone_arr(clone);
}

void	add_exported(char *arg, t_s_env ***e)
{
	char	**clone;
	int		i;

	i = 0;
	clone = ft_memalloc(sizeof(char **) * (count_strarr((**e)->exported_env) + 2));
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

void	change_public_env(char *arg, t_s_env ***e)
{
	int		i;

	i = 0;
	if (is_public(arg, (**e)->public_env))
	{
		printf("change pub\n");
		change_public(arg, &(e));
	}
	else
	{
		add_public(arg, &(e));
		if (is_local(arg, (**e)->private_env))
			delete_local(arg, &(e), 0, 0);
		if (is_exported(arg, (**e)->exported_env))
			delete_exported(arg, &(e), 0, 0);
	}
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
	if (!has_value(arg))
		tmp = ft_strjoin(arg, "=");
	else
		tmp = ft_strdup(arg);
	if (sh_getnenv(arg, (***e)->private_env))
		clone[i] = ft_strjoin(tmp, sh_getnenv(arg, (***e)->private_env));
	else
		clone[i] = ft_strdup(tmp);
	free(tmp);
	clone[++i] = NULL;
	sh_freetab(&(***e)->public_env);
	(***e)->public_env = clone_arr(clone);
	sh_freetab(&clone); 
}

void	change_public(char *arg, t_s_env ****e)
{
	int		i;
	int		len;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	len = var_name_len(arg);
	while ((***e)->public_env[i])
	{
		tmp1 = ft_strsub(arg, 0, len);
		tmp2 = ft_strsub((***e)->public_env[i], 0, len);
		if (ft_strcmp(tmp1, tmp2) == 0)
		{
			free((***e)->public_env[i]);
			(***e)->public_env[i] = ft_strdup(arg);
			free(tmp1);
			free(tmp2);
			return ;
		}
		i++;
	}
	printf("errror\n");
}
