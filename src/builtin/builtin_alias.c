/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:02:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:59:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "builtin_alias.h"
#include "builtins.h"

static void		alias_print_all(char *cmd, t_alias *alias)
{
	char		squoted;

	while (alias)
	{
		squoted = (alias->value && *alias->value == '\'') ? '\\' : '\0';
		ft_dprintf(STDOUT_FILENO, "%s %s=%c'%s%c'\n",
			cmd, alias->key, squoted, alias->value, squoted);
		alias = alias->next;
	}
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
			return (ERR_OK);
		}
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
		alias_print_all(exec->cmd[0], e->alias_list);
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
