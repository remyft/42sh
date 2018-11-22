/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:43:32 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 05:01:36 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_hist(t_hist **begin, char **env)
{
	int		continu;
	t_hist	*curr;
	int		fd;
	char	*path;

	continu = 1;
	if (!(path = get_env(env, "HOME")))
		fd = open("/tmp/.21sh_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	else
	{
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, ".21sh_history", 1);
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
		free(path);
	}
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
	curr = *begin;
	while (curr)
	{
		curr->begin = *begin;
		curr = curr->next;
	}
	close(fd);
}

void	save_history(int index, char *buff, char *buff_tmp, t_hist **curr, char **env)
{
	int		j;
	char	*term;
	int		fd;
	int		nb_col;
	t_hist	*tmp;
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
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	index = index / nb_col - 1;
	j = ft_strlen(buff) / nb_col;
	while (++index < j)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 2, ft_pchar);
	if (*curr)
	{
		if (ft_strcmp(buff, (*curr)->begin->content) != 0)
		{
			ft_putendl_fd(buff, fd);
			tmp = *curr;
			*curr = ft_memalloc(sizeof(t_hist));
			(*curr)->content = ft_strdup(buff);
			(*curr)->c_size = ft_strlen(buff);
			(*curr)->next = tmp->begin;
			tmp->begin->prev = *curr;
			(*curr)->begin = *curr;
			while ((*curr)->next)
			{
				if ((*curr)->tmp)
					free((*curr)->tmp);
				(*curr)->tmp = NULL;
				if ((*curr)->prev)
					(*curr)->begin = (*curr)->prev->begin;
				*curr = (*curr)->next;
			}
			(*curr)->begin = tmp->begin;
			*curr = (*curr)->begin;
		}
		else 
			*curr = (*curr)->begin;
	}
	else
	{
		ft_putendl_fd(buff, fd);
		*curr = ft_memalloc(sizeof(t_hist));
		(*curr)->content = ft_strdup(buff);
		(*curr)->c_size = ft_strlen(buff);
		(*curr)->begin = *curr;
	}
	ft_bzero(buff_tmp, 8194);
	close(fd);
}
