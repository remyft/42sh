/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 00:07:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/19 09:21:50 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include <signal.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "free_env.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "shell.h"
#include <sys/ioctl.h>

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

static void		get_bin_paths(char **table, size_t *size)
{
	int			fd;
	char		*line;
	int			ret;

	line = NULL;
	if ((fd = open("/etc/paths", O_RDONLY)) < 0)
		return ;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!table[*size])
			table[*size] = line;
		else if (!(table[*size] = ft_strjoinfree(table[*size], ":", 1))
			|| !(table[*size] = ft_strjoinfree(table[*size], line, 3)))
			return ;
	}
	close(fd);
	++(*size);
}

static char		**build_private_env(char **env)
{
	char		**ret;
	size_t		size;

	size = 3;
	if ((ret = ft_memalloc(sizeof(*ret) * size)) != NULL)
	{
		size = 0;
		if ((ret[size] = ft_strjoin("IFS=", IFS_DEFAULT)) != NULL)
			size++;
		if (!sh_getnenv("PATH", env))
			get_bin_paths(ret, &size);
	}
	return (ret);
}

void			init_job(t_s_env *e)
{
	if (e->interactive)
	{
		while (tcgetpgrp(STDIN_FILENO) != (e->pgid = getpgrp()))
			kill (-e->pgid, SIGTTIN);
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, SIG_DFL);
		e->pgid = getpid();
		if (setpgid(e->pgid, e->pgid) < 0)
		{
			ft_dprintf(2, "%s: setpgid error\n", e->progname);
			exit(1);
		}
		ioctl(STDIN_FILENO, TIOCSPGRP, &e->pid);
	}

}

void			init_fd(t_s_env *e)
{
	char	*tty_name;
	int		fd;

	if (e->interactive)
	{
		tty_name = ttyname(STDIN_FILENO);
		fd = open(tty_name, O_RDWR);
	}
	else
		fd = STDIN_FILENO;
	e->fd = fd;
}

void			init_shell_env(t_s_env *e, int ac, char **av, char **env)
{
	ft_memset(e, 0, sizeof(*e));
	e->ac = ac;
	e->av = av;
	e->progpath = get_path(av[0]);
	e->progname = (ft_strrchr(av[0], '/')) ? ft_strrchr(av[0], '/') + 1 : av[0];
	e->public_env = collect_env(env);
	e->private_env = build_private_env(env);
	e->ret = 0;
	e->interactive = isatty(STDIN_FILENO);
	e->pid = getpid();
	e->pgid = getpgrp();
	init_fd(e);
	init_job(e);
	e->shell_loop = 1;
}
