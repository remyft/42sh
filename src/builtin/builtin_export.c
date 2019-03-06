/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:22:25 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/06 21:38:05 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"
#include "builtin_type.h"

/*
**	export name[=word]...
**
** 	When -p is specified, export shall write to the standard output the names
**  and values of all exported variables, in the following format:
**
**	"export %s=%s\n", <name>, <value>
**	export -p
**
**	Mark each name to be passed to child processes in the environment.
**	The names refer to shell variables. If no names are supplied, or if the
**	-p option is given, a list of names of all exported variables is displayed.
**	The -p option displays output in a form that may be reused as input. If a
**	variable name is followed by =value, the value of the variable is set to
**	value.
**
**	The return status is zero unless an invalid option is supplied, one of the
**	names is not a valid shell variable name.
*/

int			builtin_export(t_execute *exec, t_s_env *e)
{
	int			i;
	int			ret;
	t_export	*export;

	export = def_s_export(exec);
	i = 0;
	ret = 0;
	while (++i <= export->cnt_opt)
	{
		ft_strchr(exec->cmd[i], 'p') ? export->opt_p = 1 : 0;
		if (illegal_option(exec->cmd[i]))
		{
			free(export);
			return (2);
		}
	}
	if (exec->cmd[i--])
	{
		while (exec->cmd[++i])
			ret += exec_export(exec->cmd[i], &e);
		free(export);
		return ((ret > 0) ? 1 : 0);
	}
	export_print(e->exported_env, e->public_env);
	free(export);
	return (0);
}

t_export	*def_s_export(t_execute *exec)
{
	t_export	*export;

	export = ft_memalloc(sizeof(t_export));
	export->opt_p = 0;
	export->cnt_opt = count_options(exec->cmd);
	return (export);
}
