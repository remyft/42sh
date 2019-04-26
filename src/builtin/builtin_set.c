/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:01:54 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/26 09:25:59 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"
#include "builtin_set.h"
#include "builtin_unset.h"

int		builtin_set(t_execute *exec, t_s_env *e)
{
	int		i;
	char	**clone;
	char	**sorted;

	if (!exec->cmd[1])
	{
		clone = clone_2_arr(e->private_env, e->public_env);
		sorted = clone_2_arr(clone, e->exported_env);
		sh_freetab(&clone);
		export_sort(&sorted);
		i = -1;
		while (sorted[++i])
			print_set(sorted[i]);
		sh_freetab(&sorted);
	}
	return (0);
}

void	print_set(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\t')
			ft_putstr("\\t");
		else if (s[i] == '\n')
			ft_putstr("\\n");
		else
			ft_putchar(s[i]);
		i++;
	}
	ft_putstr("\n");
}

void	exec_unset(char *arg, t_s_env **e)
{
	exec_unset_check(arg, &e);
}
