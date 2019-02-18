/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:02:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/18 02:28:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "builtin_alias.h"

static int		alias_print_all(char *cmd, t_alias *alias)
{
	char		squoted;

	while (alias)
	{
		squoted = (alias->value && *alias->value == '\'') ? '\\' : '\0';
		ft_dprintf(STDOUT_FILENO, "%s %s=%c'%s%c'\n",
			cmd, alias->key, squoted, alias->value, squoted);
		alias = alias->next;
	}
	return (0);
}

static int		alias_print(char **cmd, size_t pos, t_s_env *e)
{
	t_alias		*alias;
	char		squoted;

	alias = e->alias_list;
	while (alias)
	{
		if (!ft_strcmp(cmd[pos], alias->key))
		{
			squoted = (alias->value && *alias->value == '\'') ? '\\' : '\0';
			ft_dprintf(STDOUT_FILENO, "%s %s=%c'%s%c'\n",
				cmd[0], alias->key, squoted, alias->value, squoted);
			return (0);
		}
		alias = alias->next;
	}
	ft_dprintf(STDERR_FILENO, "%s: %s: %s: not found\n",
		e->progname, cmd[0], cmd[pos]);
	return (1);
}

int				builtin_alias(t_execute *exec, t_s_env *e)
{
	size_t		i;
	char		*equal;
	int			ret;

	i = 1;
	ret = 0;
	if (!exec->cmd[i])
		ret = alias_print_all(exec->cmd[0], e->alias_list);
	while (exec->cmd[i])
	{
		if ((equal = ft_strchr(exec->cmd[i], '=')) == NULL
		|| equal == exec->cmd[i])
			ret |= alias_print(exec->cmd, i, e);
		else
			ret |= alias_set(exec->cmd[i], &e->alias_list);
		i++;
	}
	return (ret);
}
