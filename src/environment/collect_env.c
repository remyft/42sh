/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 03:05:48 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 13:02:45 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		**collect_env(char **ep)
{
	char	**env;
	char	*tmp;
	int		ntmp;
	int		i;

	i = -1;
	if (!ep || !ep[0]
			|| !(env = (char**)malloc(sizeof(char*) * (get_tab_len(ep) + 2))))
		return (NULL);
	while (ep[++i])
		env[i] = ft_strdup(ep[i]);
	env[i + 1] = NULL;
	tmp = get_env(env, "SHLVL");
	ntmp = ft_atoi(tmp);
	free(tmp);
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
	int		i;
	int		j;

	i = 0;
	while (env && env[i] && !cmp_env(env[i], to_get))
		i++;
	if (env && env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		return (ft_strdup(&env[i][j + 1]));
	}
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
