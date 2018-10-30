/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:38:49 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/30 04:09:53 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			ft_pchar(int nb)
{
	return (write(STDOUT_FILENO, &nb, 1));
}

void		term_restore(struct termios save)
{
	if (tcsetattr(0, TCSANOW, &save) == -1)
	{
		ft_putendl("Fatal error: unable to restore the term attributes.");
		exit(2);
	}
}

void		define_new_term(struct termios *save)
{
	struct termios	termios;

	if (tcgetattr(0, save) != 0)
	{
		ft_putendl("Fatal error: unable to get term attributes.");
		exit(2);
	}
	if (tcgetattr(0, &termios) != 0)
	{
		ft_putendl("Fatal error: unable to the term attributes.");
		exit(2);
	}
	termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSANOW, &termios)) == -1)
	{
		ft_putendl("Fatal error: unable to set the new term attributes.");
		exit(2);
	}
}

int		go_home(int index)
{
	int		i;
	char	*term;
	int		ret;
	int		nb_col;
	char	prompt[4097];
	int		len;

	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	ret = tgetent(NULL, term);
	nb_col = tgetnum("co");
	i = (len + index) / nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, len), 1, ft_pchar);
	index = 0;
	return (index);
}

int		go_end(int index, int len)
{
	char	*term;
	int		nb_col;
	int		i;
	int		j;
	char	prompt[4097];
	int		lenp;

	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	i = (index + lenp) / nb_col - 1;
	j = (len + lenp) / nb_col;
	while (++i < j)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (len + lenp) % nb_col), 1, ft_pchar);
	return (len);
}

void	left_arrow(int *index)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		len;

	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	*index = *index > 0 ? *index - 1 : 0;
	if (*index && (*index + len) % nb_col == nb_col - 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (*index + len) % nb_col), 1, ft_pchar);
}

void	right_arrow(int *index, int i)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		len;

	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	*index = *index < i ? *index + 1 : i;
	if (*index && (*index + len) % nb_col == 0)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (*index + len) % nb_col), 1, ft_pchar);
}

int		up_arrow(int *index, char *buff, char *buff_tmp, t_hist **curr)
{
	int			i;
	size_t		len;
	char		prompt[4097];

	len = ft_strlen(buff_tmp);
	i = ft_strlen(buff);
	if (*curr && (*curr)->next && ((ft_strcmp((*curr)->content, buff) == 0 && buff_tmp[8193]) || *curr != (*curr)->begin))
	{
		if ((*curr)->tmp)
			free((*curr)->tmp);
		(*curr)->tmp = ft_strdup(buff);
		(*curr) = (*curr)->next;
		while ((*curr)->next && (ft_strstr((*curr)->content, buff_tmp) != (*curr)->content || (*curr)->c_size <= len || ft_strcmp((*curr)->content, buff) == 0))
			(*curr) = (*curr)->next;
		while ((*curr)->prev && (ft_strstr((*curr)->content, buff_tmp) != (*curr)->content || (*curr)->c_size <= len))
			(*curr) = (*curr)->prev;
	}
	else if ((*curr)->next)
	{
		len = ft_strlen(buff);
		while ((*curr)->next && (ft_strstr((*curr)->content, buff) != (*curr)->content || (*curr)->c_size <= len))
			*curr = (*curr)->next;
		if (*curr != (*curr)->begin && (ft_strstr((*curr)->content, buff) != (*curr)->content || (*curr)->c_size <= len))
			while ((*curr)->prev)
				*curr = (*curr)->prev;
		ft_strcpy(buff_tmp, buff);
		buff_tmp[8193] = 1;
	}
	if (*curr && ft_strstr((*curr)->content, buff_tmp) == (*curr)->content && (*curr)->c_size > len)
	{
		ft_bzero(buff, i);
		if ((*curr)->tmp)
			ft_strcpy(buff, (*curr)->tmp);
		else
			ft_strcpy(buff, (*curr)->content);
	}
	*index = go_home(*index);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putstr(RESET);
	ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
	ft_putstr(WHITE);
	ft_putstr(buff);
	*index = ft_strlen(buff);
	return (*index);
}

int		down_arrow(int *index, char *buff, char *buff_tmp, t_hist **curr)
{
	int		i;
	size_t	len;
	char	prompt[4097];

	len = ft_strlen(buff_tmp);
	i = ft_strlen(buff);
	if (*curr && (*curr)->prev)
	{
		if ((*curr)->tmp)
			free((*curr)->tmp);
		(*curr)->tmp = ft_strdup(buff);
		*curr = (*curr)->prev;
		while ((*curr)->prev && (ft_strstr((*curr)->content, buff_tmp) != (*curr)->content || (*curr)->c_size <= len || ft_strcmp((*curr)->content, buff) == 0))
			*curr = (*curr)->prev;
		if (ft_strstr((*curr)->content, buff_tmp) == (*curr)->content && (*curr)->c_size > len)
		{
			ft_bzero(buff, i);
			if ((*curr)->tmp)
				ft_strcpy(buff, (*curr)->tmp);
			else
				ft_strcpy(buff, (*curr)->content);
		}
		else
		{
			ft_bzero(buff, i);
			ft_strcpy(buff, buff_tmp);
		}
	}
	else if (*curr && buff_tmp[8193])
	{
		ft_bzero(buff, i);
		ft_strcpy(buff, buff_tmp);
		ft_bzero(buff_tmp, 8194);
	}
	*index = go_home(*index);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putstr(RESET);
	ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
	ft_putstr(WHITE);
	ft_putstr(buff);
	*index = ft_strlen(buff);
	return (*index);
}

void	ft_exit2(struct termios save, t_hist **begin)
{
	t_hist *curr;

	term_restore(save);
	ft_putchar('\n');
	if (*begin)
		while (*begin)
		{
			curr = (*begin)->next;
			if ((*begin)->content)
				free((*begin)->content);
			if ((*begin)->tmp)
				free((*begin)->tmp);
			free(*begin);
			(*begin) = curr;
		}
	exit(0);
}

int		ft_cancel(int index, int i, char *buff_tmp, t_hist **curr)
{
	char	*term;
	int		ret;
	int		nb_col;

	term = getenv("TERM");
	ret = tgetent(NULL, term);
	nb_col = tgetnum("co");
	i = i % nb_col < nb_col ? i + (nb_col - i % nb_col) : i;
	while ((index = index + nb_col) < i)
		ft_putchar('\n');
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	*curr = (*curr)->begin;
	ft_bzero(buff_tmp, 8194);
	while ((*curr)->next)
	{
		if ((*curr)->tmp)
			free((*curr)->tmp);
		(*curr)->tmp = NULL;
		(*curr) = (*curr)->next;
	}
	if ((*curr)->tmp)
		free((*curr)->tmp);
	(*curr)->tmp = NULL;
	*curr = (*curr)->begin;
	return (-1);
}

void	del_lines(int index, int len, int nb_col)
{
	int		i;
	int		j;
	char	prompt[4097];
	int		lenp;

	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	i = (index + lenp) / nb_col - 1;
	j = (len + lenp) / nb_col;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	while (++i < j)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("dl", NULL), 1, ft_pchar);
	}
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
}

int		del_left(int *index, char *buff, char *buff_tmp, t_hist *curr)
{
	int		j;
	char	*term;
	int		len;
	int		nb_col;
	int		i;
	char	prompt[4097];

	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	j = 0;
	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	i = ft_strlen(buff);
	if (*index && (*index + len) % nb_col == 0)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	if (*index != 0)
	{
		*index = *index > 0 ? *index - 1 : 0;
		while (*index + j < i)
		{
			buff[*index + j] = buff[*index + j + 1];
			j++;
		}
		buff[i] = '\0';
		i = i > 0 ? i - 1 : 0;
		tputs(tgoto(tgetstr("ch", NULL), 0, (*index + len) % nb_col), 1, ft_pchar);
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
	}
	if ((*index + len) % nb_col == nb_col - 1)
	{
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		ft_putchar(' ');
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (i + len > nb_col - 1)
	{
		del_lines(*index, i, nb_col);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		*index < i ? ft_putstr(&buff[*index]) : ft_putstr("");
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (curr && ft_strcmp(curr->content, buff) != 0)
		ft_strcpy(buff_tmp, buff);
	return (i);
}

void	del_right(int index, int *i, char *buff)
{
	int		j;
	char	*term;
	int		ret;
	int		nb_col;

	term = getenv("TERM");
	ret = tgetent(NULL, term);
	nb_col = tgetnum("co");
	j = -1;
	while (index + ++j < *i)
		buff[index + j] = buff[index + j + 1];
	tputs(tgetstr("dc", NULL), 1, ft_pchar);
	del_lines(index, *i, nb_col);
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	index < *i ? ft_putstr(&buff[index]) : ft_putstr("");
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	*i = *i > index ? *i - 1 : index;
}

void	ft_clear(char *buff)
{
	char	prompt[4097];

	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	ft_putstr(RESET);
	ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
	ft_putstr(WHITE);
	ft_putstr(buff);
}

void	next_word(int *index, int len, char *buff)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		lenp;

	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	while (buff[*index] != ' ' && *index < len)
	{
		if (len > nb_col)
			if ((*index + lenp) % nb_col == 0 && *index < len)
				tputs(tgetstr("do", NULL), 1, ft_pchar);
		*index = *index + 1;
	}
	while (*index < len && buff[*index] == ' ')
		*index = *index + 1;
	tputs(tgoto(tgetstr("ch", NULL), 0, (*index + lenp) % nb_col), 1, ft_pchar);
}

void	prev_word(int *index, int len, char *buff)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		lenp;

	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	if (*index == len && len != 0)
		*index = *index - 1;
	if (ft_isprint(buff[*index]) && buff[*index] != ' ' && *index > 0)
		*index = *index - 1;
	while (buff[*index] == ' ')
		*index = *index - 1;
	while (buff[*index] != ' ' && *index > 0)
	{
		if (len > nb_col)
			if ((*index + lenp) % nb_col == 0 && *index > 0)
				tputs(tgetstr("up", NULL), 1, ft_pchar);
		*index = *index - 1;
	}
	while (*index > 0 && buff[*index] == ' ')
		*index = *index + 1;
	tputs(tgoto(tgetstr("ch", NULL), 0, (*index + lenp) % nb_col), 1, ft_pchar);
}

int		get_typing(int *index, char *buff, char *tmp, int nb_read, char *buff_tmp)
{
	int		len;
	int		cp;
	int		j;
	char	cbis;
	char	tchar;

	cp = 0;
	len = ft_strlen(buff);
	if (ft_isprint(tmp[0]))
		ft_bzero(buff_tmp, 8194);
	while (cp < nb_read && (ft_isprint(tmp[cp]) || (tmp[0] == 9 && !buff[0])))
	{
		tchar = buff[*index + 1];
		if (*index != len)
			buff[*index + 1] = buff[*index];
		buff[(*index)++] = tmp[cp];
		len++;
		j = 1;
		ft_putchar(tmp[cp++]);
		if (*index != len)
		{
			while (*index + j < len)
			{
				cbis = buff[*index + j];
				buff[*index + j] = tchar;
				tchar = cbis;
				j++;
			}
			tputs(tgetstr("sc", NULL), 1, ft_pchar);
			ft_putstr(&buff[*index]);
			tputs(tgetstr("rc", NULL), 1, ft_pchar);
		}
	}
	return (len);
}

void	deal_commande(int index, char *buff, char *buff_tmp, t_hist **curr, char **env)
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
