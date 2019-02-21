/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 00:07:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/21 05:40:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "free_env.h"
#include "shell_env.h"
#include "shell.h"

static char		*get_path(char *prog)
{
	char		*pwd;
	char		*ptr;
	char		*slsh;

	if (*prog == '/')
		return (ft_strdup(prog));
	pwd = ft_strjoinfree(ft_strjoinfree(getcwd(NULL, 0), "/", 1), prog, 1);
	ptr = pwd;
	while (ptr && (slsh = ft_strchr(ptr + 1, '/')))
	{
		if (!ft_strncmp(ptr + 1, ".", slsh - ptr - 1))
			ft_strcpy(ptr, slsh);
		else if (!ft_strncmp(ptr + 1, "..", slsh - ptr - 1))
		{
			if (ptr > pwd)
			{
				while (--(*ptr) != '/')
					;
				ft_strcpy(ptr, slsh);
			}
		}
		else
			ptr = slsh;
	}
	return (pwd);
}

static char		**build_private_env(void)
{
	char		**ret;

	if (!(ret = ft_memalloc(sizeof(*ret) * 2)))
		return (NULL);
	ret[0] = ft_strjoin("IFS=", IFS_SEPARATORS);
	return (ret);
}

void			init_shell_env(t_s_env *e, int ac, char **av, char **env)
{
	ft_memset(e, 0, sizeof(*e));
	e->ac = ac;
	e->av = av;
	e->progpath = get_path(av[0]);
	e->progname = (ft_strrchr(av[0], '/')) ? ft_strrchr(av[0], '/') + 1 : av[0];
	e->public_env = collect_env(env);
	e->private_env = build_private_env();
	e->ret = 0;
	e->pid = getpid();
	e->shell_loop = 1;
}

static void		free_aliases(t_alias *alias)
{
	if (!alias)
		return ;
	free_aliases(alias->next);
	if (alias->key)
		free(alias->key);
	if (alias->value)
		free(alias->value);
	free(alias);
}

void			free_shell_env(t_s_env *e)
{
	if (e->progpath)
		free(e->progpath);
	free_tab(&e->public_env);
	free_tab(&e->private_env);
	free_aliases(e->alias_list);
}
