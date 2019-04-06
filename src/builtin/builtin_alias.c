/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:02:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/04 16:44:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "builtin_alias.h"
#include "builtins.h"

static int		alias_print_alias(char *cmd, t_alias *alias)
{
	size_t		i;

	i = 0;
	ft_dprintf(STDOUT_FILENO, "%s %s='", cmd, alias->key);
	while (alias->value[i])
	{
		if (alias->value[i] == '\'')
			ft_dprintf(STDOUT_FILENO, "'\\''");
		else
			ft_dprintf(STDOUT_FILENO, "%c", alias->value[i]);
		i++;
	}
	ft_dprintf(STDOUT_FILENO, "'\n");
	return (ERR_OK);
}

static int		alias_print_all(char *cmd, t_alias *alias)
{
	while (alias)
	{
		alias_print_alias(cmd, alias);
		alias = alias->next;
	}
	return (ERR_OK);
}

static int		alias_print(char **cmd, size_t pos, t_s_env *e)
{
	t_alias		*alias;

	alias = e->alias_list;
	while (alias)
	{
		if (!ft_strcmp(cmd[pos], alias->key))
			return (alias_print_alias(cmd[0], alias));
		alias = alias->next;
	}
	return (ERR_NOT_FOUND);
}

int				builtin_alias(t_execute *exec, t_s_env *e)
{
	size_t		i;
	char		*equal;
	int			error;
	int			ret;

	i = 1;
	ret = 0;
	error = 0;
	if (!exec->cmd[i])
		return (alias_print_all(exec->cmd[0], e->alias_list));
	while (exec->cmd[i])
	{
		if ((equal = ft_strchr(exec->cmd[i], '=')) == NULL
		|| equal == exec->cmd[i])
			error = alias_print(exec->cmd, i, e);
		else
			error = alias_set(exec->cmd[i], &e->alias_list);
		if (error)
		{
			ret = alias_error(error, exec->cmd[0], exec->cmd[i], e->progname);
			error = 0;
		}
		i++;
	}
	return (ret);
}
