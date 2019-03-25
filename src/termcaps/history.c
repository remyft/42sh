/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:43:32 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/24 20:44:48 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"
#include "history.h"

static void		get_old_hist(t_hist **begin, int fd, int continu)
{
	t_hist	*curr;

	while (continu)
	{
		if (!(curr = ft_memalloc(sizeof(t_hist))))
			return ;
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
			free(curr->content);
			free(curr);
			if (*begin)
				(*begin)->prev = NULL;
		}
		else
			*begin = curr;
	}
}

void			create_hist(t_hist **begin, char **env)
{
	t_hist	*curr;
	int		fd;
	char	*path;

	if (!(path = get_env(env, "HOME")))
		fd = open(TMP_PATH, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
	{
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, HIST_NAME, 1);
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

static t_hist	*fill_hist(char *buff, int fd)
{
	int		i;
	t_hist	*curr;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		ft_putchar_fd(buff[i++], fd);
	ft_putchar_fd('\n', fd);
	if (!(curr = ft_memalloc(sizeof(t_hist))))
		return (NULL);
	if (!(curr->content = strdup_until(buff, '\n')))
	{
		free(curr);
		return (NULL);
	}
	curr->c_size = ft_strlen_ch(buff, '\n');
	curr->begin = curr;
	return (curr);
}

static void		get_new_hist(t_hist **curr, char *buff, int fd)
{
	if (*curr)
	{
		if (ft_strcmp(buff, (*curr)->begin->content) != 0)
		{
			(*curr) = (*curr)->begin;
			if (!((*curr)->prev = fill_hist(buff, fd)))
				return ;
			(*curr)->prev->next = *curr;
			(*curr) = (*curr)->prev;
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
		*curr = fill_hist(buff, fd);
}

void			save_history(t_line *line, char *buff, t_hist **curr,
		char **env)
{
	int		j;
	int		fd;
	int		index;
	char	*path;

	if (!(path = get_env(env, "HOME")))
		fd = open(TMP_PATH, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
	{
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, HIST_NAME, 1);
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
		free(path);
	}
	index = line->index / line->nb_col - 1;
	j = ft_strlen(buff) / line->nb_col;
	get_new_hist(curr, buff, fd);
	close(fd);
}
