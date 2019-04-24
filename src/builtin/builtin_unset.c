/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:28:26 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/22 18:25:54 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "shell_lib.h"
#include "builtin_unset.h"
#include "builtin_export.h"

int		builtin_unset(t_execute *exec, t_s_env *e)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (exec->cmd[i])
	{
		if (!valid_id_unset(exec->cmd[i]))
			ret = 1;
		else
			exec_unset(exec->cmd[i], &e);
		i++;
	}
	return (ret);
}

int		valid_id_unset(char *arg)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(arg[0]) && arg[0] != '_') ||
		(!has_invalid_id_unset(arg)))
	{
		ft_dprintf(2, "42sh: unset: `%s': not a valid identifier\n",
				arg);
		return (0);
	}
	return (1);
}

int		has_invalid_id_unset(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	exec_unset_check(char *arg, t_s_env ***e)
{
	if (is_local(arg, (**e)->private_env))
		delete_local(arg, &e, 0, 0);
	if (is_public(arg, (**e)->public_env))
		delete_public(arg, &e, 0, 0);
	if (is_exported(arg, (**e)->exported_env))
		delete_exported(arg, &e, 0, 0);
}

void	delete_public(char *arg, t_s_env ****e, int i, int j)
{
	char	**clone;
	char	*tmp1;
	char	*tmp2;

	clone = ft_memalloc(sizeof(char **) *
			(count_strarr((***e)->public_env)));
	tmp1 = ft_strsub(arg, 0, var_name_len(arg));
	while ((***e)->public_env[i])
	{
		tmp2 = ft_strsub((***e)->public_env[i], 0,
				var_name_len((***e)->public_env[i]));
		(ft_strcmp(tmp1, tmp2) == 0) ? i++ : i;
		if (!((***e)->public_env[i]))
		{
			free(tmp2);
			break ;
		}
		clone[j++] = ft_strdup((***e)->public_env[i++]);
		free(tmp2);
	}
	free(tmp1);
	clone[j] = NULL;
	sh_freetab(&(***e)->public_env);
	(***e)->public_env = clone_arr(clone);
	sh_freetab(&clone);
}
