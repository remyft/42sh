/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 11:57:55 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "job_control.h"

static int		command_pipe_error(const char *err, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: %s failed.\n", e->progname, err);
	if (e->forked)
		exit(EXIT_FAILURE);
	return (1);
}

static int		command_pipe_left(t_jobs *jobs, t_process *p, t_s_env *e, int pfd[2], int *ppfd)
{
	t_s_env		newe;

	if (ppfd[0])
	{
		dup2(ppfd[0], STDIN_FILENO);
		close(ppfd[0]);
	}
	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.private_env = sh_tabdup((const char **)e->private_env);
	//newe.forked = 1;
	sleep(1);
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	command_check(jobs, p, &newe);
	//command_parse(((t_pipeline *)cmd)->left, &newe, 0);
	close(STDOUT_FILENO);
	sh_freetab(&newe.public_env);
	sh_freetab(&newe.private_env);
	//exit(newe.ret);
	return (1);
}

static int		command_pipe_right(t_jobs *jobs, t_process *p, t_s_env *e, int pfd[2])
{
	t_s_env		newe;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)e->public_env);
	newe.private_env = sh_tabdup((const char **)e->private_env);
	newe.forked = 1;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	command_check(jobs, p, &newe);
	//command_parse(((t_pipeline *)cmd)->right, &newe, 0);
	close(STDIN_FILENO);
	sh_freetab(&newe.public_env);
	sh_freetab(&newe.private_env);
	//exit(newe.ret);
	return (1);
}

static int		command_last_pipe(t_jobs *jobs, int pfd[2], t_process *p, t_s_env *e)
{
	//pid_t		pid;

	//printf("Laucnhing command :%s\n", ((t_execute *)p->exec)->cmd[0]);
	//if ((pid = fork()) < 0)
	//	return (command_pipe_error("fork()", e));
	//else if (pid == 0)
	command_pipe_right(jobs, p, e, pfd);
	close(pfd[0]);
	//command_wait2(pid, NULL, e);
	return (0);
}

int				command_pipe(t_jobs *jobs, t_process *p, t_s_env *e, int ppfd[2])
{
	//pid_t		pid;
	int			pfd[2];

	if (pipe(pfd) < 0)
		return (command_pipe_error("pipe()", e));
	//if ((pid = fork()) < 0)
	//	return (command_pipe_error("fork()", e));
	//command_parse(((t_pipeline *)cmd)->left, &newe);
	//else if (pid == 0)
	command_pipe_left(jobs, p, e, pfd, ppfd);
	if (ppfd[0])
		close(ppfd[0]);
	close(pfd[1]);
	if (p->next && p->next->type & PIPED)
	{
		if (command_pipe(jobs, p->next, e, pfd))
			return (1);
	}
	else if (command_last_pipe(jobs, pfd, p->next, e))
		return (1);
	//command_wait2(pid, NULL, e);
	return (0);
}
