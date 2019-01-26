/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:20:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/26 06:03:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "builtin_cd.h"

static size_t	builtin_cd_args(char **args)
{
	size_t		i;
	size_t		j;
	char		*tmp;

	i = 1;
	while (args[i] && args[i][0] == '-' && args[i][1])
	{
		j = 1;
		if (!ft_strcmp(args[i], "--"))
			return (i + 1);
		while (args[i][j])
		{
			if (args[i][j] != 'P' && args[i][j] != 'L')
				return (cd_error(ERR_INVALID_OPTION, args[i] + j) - 1);
			j++;
		}
		i++;
	}
	return (i);
}

int				buitltin_cd(char **args, t_s_env *e)
{
	size_t		i;

	if (!(i = cd_args(args)))
		return (1);
	if (!args[i] || !args[i + 1])
		return (cd_write_in_pwd(args, e, i));
	if (!args[i + 2])
		return (cd_search_in_pwd(args + i - 1, e));
	return (cd_error(ERR_TOO_MUCH_ARGUMENT, args[1]));
}
