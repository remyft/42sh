/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:25:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 20:34:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_env.h"

static char		**ft_env_opt_u(char **cmd, int *i, int j, t_e_opt *opt)
{
	char		**tab;
	int			k;

	if (!(tab = (char **)malloc(sizeof(*tab) * (ft_tablen(opt->ptr) + 2))))
		return (opt->ptr);
	k = 0;
	while (opt->ptr && opt->ptr[k])
	{
		tab[k] = ft_strdup(opt->ptr[k]);
		k++;
	}
	tab[k] = (cmd[*i][j] == '\0') ?
		ft_strdup(cmd[++(*i)]) : ft_strdup(&cmd[*i][j]);
	tab[k + 1] = NULL;
	if (opt->ptr)
		ft_freetab(&opt->ptr);
	return (tab);
}

static char		*ft_env_opt_p(char **cmd, int *i, int j, t_e_opt *opt)
{
	char		*ret;
	int			len;

	len = ft_strlen(opt->path);
	len += (cmd[*i][j] == 0) ? ft_strlen(cmd[*i + 1]) : ft_strlen(&cmd[*i][j]);
	if (!(ret = (char *)malloc(sizeof(*ret) * (len + 2))))
		return (opt->path);
	ft_bzero(ret, len + 2);
	ft_strcpy(ret, opt->path);
	if (opt->path)
	{
		ft_freestr(&opt->path);
		ft_strcat(ret, ":");
	}
	if (cmd[*i][j] == '\0')
		ft_strcat(ret, cmd[++(*i)]);
	else
		ft_strcat(ret, &cmd[*i][j]);
	return (ret);
}

static int		env_opt_pu(char **cmd, t_e_opt *opt, int *i, int j)
{
	char		**old;
	char		*tmp;

	if (cmd[*i][j] == 'P')
	{
		opt->p = 1;
		tmp = opt->path;
		if ((opt->path = ft_env_opt_p(cmd, i, j + 1, opt)) == tmp)
			return (ft_enverror("malloc failed", 0, opt));
	}
	else if (cmd[*i][j] == 'u')
	{
		opt->u = 1;
		old = opt->ptr;
		if ((opt->ptr = ft_env_opt_u(cmd, i, j + 1, opt)) == old)
			return (ft_enverror("malloc failed", 0, opt));
	}
	else
		return (ft_enverror("illegal option", cmd[*i][j], opt));
	return (0);
}

int				builtin_env_check(int *i, int *j, char **cmd, t_e_opt *opt)
{
	while (cmd[++(*i)] && cmd[*i][0] == '-')
	{
		if (!cmd[*i][1])
			opt->i = 1;
		if (!ft_strcmp(cmd[*i], "--"))
			return (*i);
		j = 0;
		while (cmd[*i][++(*j)])
		{
			if (cmd[*i][*j] == '-' || cmd[*i][*j] == 'i')
				opt->i = 1;
			else if (cmd[*i][*j] == 'v')
				opt->v = 1;
			else if (cmd[*i][*j] == 'P' || cmd[*i][*j] == 'u')
				return (env_opt_pu(cmd, opt, i, *j));
			else
				return (ERR_ILLEGAL_OPT);
		}
	}
	return (ERR_OK);
}

// int				ft_env_check_opt_plus(char **cmd, t_opt *opt, int i)
// {
// 	char		**tab;
// 	int			j;

// 	while (ft_strchr(cmd[i], '=') != NULL)
// 	{
// 		if ((tab = (char **)malloc(ft_tablen(opt->extra) + 2)) == NULL)
// 			return (ft_enverror("malloc failed", 0, opt));
// 		j = 0;
// 		while (opt->extra && opt->extra[j])
// 		{
// 			tab[j] = opt->extra[j];
// 			j++;
// 		}
// 		tab[j] = cmd[i];
// 		tab[j + 1] = NULL;
// 		ft_freetab(&opt->extra);
// 		opt->extra = tab;
// 		i++;
// 	}
// 	return (i);
// }
