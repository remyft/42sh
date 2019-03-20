/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 03:05:48 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/18 20:05:32 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "shell_lib.h"

char		**collect_env(char **ep)
{
	char	**env;
	char	*tmp;
	int		ntmp;
	int		i;

	i = -1;
	if (!ep || !ep[0]
			|| !(env = ft_memalloc(sizeof(char*) * (get_tab_len(ep) + 2))))
		return (NULL);
	while (ep[++i])
		if (!(env[i] = ft_strdup(ep[i])))
			break ;
	env[i + 1] = NULL;
	tmp = getenv("SHLVL");
	if (ft_strlen(tmp) >= 10)
	{
		ft_putstr("21sh: warning: shell level too high");
		ft_putendl(" resetting to 1");
		ntmp = 1;
	}
	else
		ntmp = ft_atoi(tmp);
	tmp = ft_strjoinfree("SHLVL=", ft_itoa(ntmp + 1), 2);
	ft_setenv(&env, tmp, 2);
	free(tmp);
	return (env);
}

static int	cmp_env(char *env, char *new)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_occuc(new, '='))
		tmp = ft_strjoin(new, "=");
	else
		tmp = ft_strdup(new);
	while (env[i] && env[i] == tmp[i] && env[i] != '=')
		i++;
	if (i != 0 && env[i] == '=' && env[i] == tmp[i])
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char		*get_env(char **env, char *to_get)
{
	char	*ptr;

	if ((ptr = sh_getnenv((const char *)to_get, env)))
		return (ft_strdup(ptr));
	return (NULL);
}

void		ft_setenv(char ***env, char *new, int len)
{
	int i;

	i = 1;
	if (len == 2 && ft_occuc(new, '='))
	{
		while ((*env)[i])
		{
			if (ft_strcmp((*env)[i], new) == 0)
				return ;
			else if (cmp_env((*env)[i], new))
			{
				free((*env)[i]);
				(*env)[i] = ft_strdup(new);
				return ;
			}
			i++;
		}
		*env = ft_ralloc(env, 1);
		(*env)[i] = ft_strdup(new);
		(*env)[++i] = NULL;
	}
	else if (len != 2)
		ft_putendl("setenv : Too many arguments");
}
