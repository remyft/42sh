/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:43:32 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/30 20:13:59 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	get_old_hist(t_hist **begin, int fd, int continu)
{
	t_hist	*curr;

	while (continu)
	{
		curr = ft_memalloc(sizeof(t_hist));
		if (*begin)
		{
			curr->next = *begin;
			(*begin)->prev = curr;
			curr->begin = *begin;
		}
		continu = get_next_line(fd, &(curr->content));
		if (curr->content)
			curr->c_size = ft_strlen(curr->content);
		if (!continu)
		{
			free(curr);
			curr = NULL;
			if (*begin)
				(*begin)->prev = NULL;
		}
		else
			*begin = curr;
	}
}

void		create_hist(t_hist **begin, char **env)
{
	t_hist	*curr;
	int		fd;
	char	*path;

	if (!(path = get_env(env, "HOME")))
		fd = open("/tmp/.21sh_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	else
	{
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, ".21sh_history", 1);
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
		free(path);
	}
	get_old_hist(begin, fd, 1);
	curr = *begin;
	while (curr)
	{
		curr->begin = *begin;
		curr = curr->next;
	}
	close(fd);
}

void		fill_hist(t_hist **curr, char *buff, int fd)
{
	ft_putendl_fd(buff, fd);
	*curr = ft_memalloc(sizeof(t_hist));
	(*curr)->content = ft_strdup(buff);
	(*curr)->c_size = ft_strlen(buff);
	(*curr)->begin = *curr;
}

void		get_new_hist(t_hist **curr, char *buff, int fd)
{
	if (*curr)
	{
		if (ft_strcmp(buff, (*curr)->begin->content) != 0)
		{
			(*curr) = (*curr)->begin;
			fill_hist(&((*curr)->prev), buff, fd);
			(*curr)->prev->next = *curr;
			while ((*curr)->next)
			{
				if ((*curr)->tmp)
					free((*curr)->tmp);
				(*curr)->tmp = NULL;
				if ((*curr)->prev)
					(*curr)->begin = (*curr)->prev->begin;
				*curr = (*curr)->next;
			}
			*curr = (*curr)->prev;
		}
		*curr = (*curr)->begin;
	}
	else
		fill_hist(curr, buff, fd);
}

void		save_history(t_line *line, char *buff, t_hist **curr, char **env)
{
	int		j;
	int		fd;
	int		index;
	char	*path;

	if (!(path = get_env(env, "HOME")))
		fd = open("/tmp/.21sh_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	else
	{
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, ".21sh_history", 1);
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
		free(path);
	}
	index = line->index / line->nb_col - 1;
	j = ft_strlen(buff) / line->nb_col;
	while (++index < j)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 2, ft_pchar);
	get_new_hist(curr, buff, fd);
	close(fd);
}
