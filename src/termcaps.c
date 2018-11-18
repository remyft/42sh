/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:38:49 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/18 03:20:55 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_down(void)
{
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
}

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

void	go_home(t_line *line)
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
	i = (len + line->index) / nb_col;
	while (i--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, len), 1, ft_pchar);
	line->index = 0;
}

void	go_end(t_line *line)
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
	i = (line->index + lenp) / nb_col - 1;
	j = (line->len + lenp) / nb_col;
	while (++i < j)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->len + lenp) % nb_col), 1, ft_pchar);
	line->index = line->len;
}

void	left_arrow(t_line *line)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		len;

	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	line->index = line->index > 0 ? line->index - 1 : 0;
	if (line->index && (line->index + len) % nb_col == nb_col - 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + len) % nb_col), 1, ft_pchar);
}

void	right_arrow(t_line *line)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		len;

	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	line->index = line->index < line->len ? line->index + 1 : line->len;
	if (line->index && (line->index + len) % nb_col == 0)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + len) % nb_col), 1, ft_pchar);
}

void	up_arrow(t_line *line)
{
	int			i;
	size_t		len;
	char		prompt[4097];

	len = ft_strlen(line->buff_tmp);
	i = ft_strlen(line->buff);
	if (line->curr && line->curr->next && ((ft_strcmp(line->curr->content, line->buff) == 0 && line->buff_tmp[8193]) || line->curr != line->curr->begin))
	{
		if (line->curr->tmp)
			free(line->curr->tmp);
		line->curr->tmp = ft_strdup(line->buff);
		line->curr = line->curr->next;
		while (line->curr->next && (ft_strstr(line->curr->content, line->buff_tmp) != line->curr->content || line->curr->c_size <= len || ft_strcmp(line->curr->content, line->buff) == 0))
			line->curr = line->curr->next;
		while (line->curr->prev && (ft_strstr(line->curr->content, line->buff_tmp) != line->curr->content || line->curr->c_size <= len))
			line->curr = line->curr->prev;
	}
	else if (line->curr->next)
	{
		len = ft_strlen(line->buff);
		while (line->curr->next && (ft_strstr(line->curr->content, line->buff) != line->curr->content || line->curr->c_size <= len))
			line->curr = line->curr->next;
		if (line->curr != line->curr->begin && (ft_strstr(line->curr->content, line->buff) != line->curr->content || line->curr->c_size <= len))
			while (line->curr->prev)
				line->curr = line->curr->prev;
		ft_strcpy(line->buff_tmp, line->buff);
		line->buff_tmp[8193] = 1;
	}
	if (line->curr && ft_strstr(line->curr->content, line->buff_tmp) == line->curr->content && line->curr->c_size > len)
	{
		ft_bzero(line->buff, i);
		if (line->curr->tmp)
			ft_strcpy(line->buff, line->curr->tmp);
		else
			ft_strcpy(line->buff, line->curr->content);
	}
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putstr(RESET);
	ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
	ft_putstr(WHITE);
	ft_putstr(line->buff);
	line->index = ft_strlen(line->buff);
	line->len = line->index;
}

void	down_arrow(t_line *line)
{
	int		i;
	size_t	len;
	char	prompt[4097];

	len = ft_strlen(line->buff_tmp);
	i = ft_strlen(line->buff);
	if (line->curr && line->curr->prev)
	{
		if (line->curr->tmp)
			free(line->curr->tmp);
		line->curr->tmp = ft_strdup(line->buff);
		line->curr = line->curr->prev;
		while (line->curr->prev && (ft_strstr(line->curr->content, line->buff_tmp) != line->curr->content || line->curr->c_size <= len || ft_strcmp(line->curr->content, line->buff) == 0))
			line->curr = line->curr->prev;
		if (ft_strstr(line->curr->content, line->buff_tmp) == line->curr->content && line->curr->c_size > len)
		{
			ft_bzero(line->buff, i);
			if (line->curr->tmp)
				ft_strcpy(line->buff, line->curr->tmp);
			else
				ft_strcpy(line->buff, line->curr->content);
		}
		else
		{
			ft_bzero(line->buff, i);
			ft_strcpy(line->buff, line->buff_tmp);
		}
	}
	else if (line->curr && line->buff_tmp[8193])
	{
		ft_bzero(line->buff, i);
		ft_strcpy(line->buff, line->buff_tmp);
		ft_bzero(line->buff_tmp, 8194);
	}
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putstr(RESET);
	ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
	ft_putstr(WHITE);
	ft_putstr(line->buff);
	line->index = ft_strlen(line->buff);
	line->len = line->index;
}

void	ft_exit2(t_line *line)
{
	t_hist *curr;

	if (line->buff[0])
		return ;
	term_restore(line->save);
	if (line->tree[0])
		free_tree(line->tree[0]);
	if (line->tree[1])
		free_tree(line->tree[1]);
	if (line->tree[2])
		free_tree(line->tree[2]);
	ft_putchar('\n');
	if (line->curr)
		while (line->curr)
		{
			curr = line->curr->next;
			if (line->curr->content)
				free(line->curr->content);
			if (line->curr->tmp)
				free(line->curr->tmp);
			free(line->curr);
			line->curr = curr;
		}
	exit(0);
}

static int		ft_cancel(int index, int i, char *buff_tmp, t_hist **curr)
{
	char	*term;
	int		nb_col;

	term = getenv("TERM");
	tgetent(NULL, term);
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

void	deal_cancel(t_line *line)
{
	if (*(line->e_cmpl) & COMPLETION)
	{
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		put_prompt();
		ft_bzero(line->buff, line->len);
		ft_strcpy(line->buff, line->buff_tmp);
		ft_bzero(line->buff_tmp, 8194);
		ft_putstr(line->buff);
		line->index = ft_strlen(line->buff);
		line->len = line->index;
		reset_put(line->tree[0]);
		reset_put(line->tree[1]);
		if (line->tree[2])
			reset_put(line->tree[2]);
		line->tmp[0] = 3;
	}
	else
	{
		if (line->tree[2])
			free_tree(line->tree[2]);
		line->tree[2] = NULL;
		line->tmp[0] = ft_cancel(line->index, line->len, line->buff_tmp, &(line->curr));
	}
	*(line->e_cmpl) &= ~COMPLETION;
}

void	del_lines(t_line *line)
{
	int		i;
	int		j;
	char	prompt[4097];
	int		lenp;
	char	*term;
	int		nb_col;

	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	i = (line->index + lenp) / nb_col - 1;
	j = (line->len + lenp) / nb_col;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	while (++i < j)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("dl", NULL), 1, ft_pchar);
	}
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
}

static void	del_left(t_line *line)
{
	int		j;
	char	*term;
	int		len;
	int		nb_col;
	char	prompt[4097];

	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	j = 0;
	len = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	line->len = ft_strlen(line->buff);
	if (line->index && (line->index + len) % nb_col == 0)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	if (line->index != 0)
	{
		line->index = line->index > 0 ? line->index - 1 : 0;
		while (line->index + j < line->len)
		{
			line->buff[line->index + j] = line->buff[line->index + j + 1];
			j++;
		}
		line->buff[line->len] = '\0';
		line->len = line->len > 0 ? line->len - 1 : 0;
		tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + len) % nb_col), 1, ft_pchar);
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
	}
	if ((line->index + len) % nb_col == nb_col - 1)
	{
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		ft_putchar(' ');
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (line->len + len > nb_col - 1)
	{
		del_lines(line);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		line->index < line->len ? ft_putstr(&(line->buff[line->index])) : ft_putstr("");
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (line->curr && ft_strcmp(line->curr->content, line->buff) != 0)
		ft_strcpy(line->buff_tmp, line->buff);
}

void	deal_dleft(t_line *line)
{
	if (*(line->e_cmpl) & COMPLETION)
	{
		delete_down();
		*(line->e_cmpl) &= ~COMPLETION;
		ft_bzero(line->buff_tmp, 8194);
	}
	else
		del_left(line);
}

void	del_right(t_line *line)
{
	int		j;
	char	*term;
	int		nb_col;

	if (*(line->e_cmpl) & COMPLETION)
		line->tmp[0] = 10;
	else
	{
		term = getenv("TERM");
		tgetent(NULL, term);
		nb_col = tgetnum("co");
		j = -1;
		while (line->index + ++j < line->len)
			line->buff[line->index + j] = line->buff[line->index + j + 1];
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
		del_lines(line);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		line->index < line->len ? ft_putstr(&(line->buff)[line->index]) : ft_putstr("");
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
		line->len = line->len > line->index ? line->len - 1 : line->index;
	}
}

void	ft_clear(t_line *line)
{
	char	prompt[4097];

	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	ft_putstr(RESET);
	ft_putend_cl(ft_strrchr(getcwd(prompt, 4097), '/') + 1, RED,  " $> ", BLUE);
	ft_putstr(WHITE);
	ft_putstr(line->buff);
}

void	next_word(t_line *line)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		lenp;

	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	while (line->buff[line->index] != ' ' && line->index < line->len)
	{
		if (line->len > nb_col)
			if ((line->index + lenp) % nb_col == 0 && line->index < line->len)
				tputs(tgetstr("do", NULL), 1, ft_pchar);
		line->index = line->index + 1;
	}
	while (line->index < line->len && line->buff[line->index] == ' ')
		line->index = line->index + 1;
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + lenp) % nb_col), 1, ft_pchar);
}

void	prev_word(t_line *line)
{
	char	*term;
	int		nb_col;
	char	prompt[4097];
	int		lenp;

	term = getenv("TERM");
	tgetent(NULL, term);
	nb_col = tgetnum("co");
	lenp = ft_strlen(ft_strrchr(getcwd(prompt, 4097), '/')) + 3;
	if (line->index == line->len && line->len != 0)
		line->index = line->index - 1;
	if (ft_isprint(line->buff[line->index]) && line->buff[line->index] != ' ' && line->index > 0)
		line->index = line->index - 1;
	while (line->buff[line->index] == ' ')
		line->index = line->index - 1;
	while (line->buff[line->index] != ' ' && line->index > 0)
	{
		if (line->len > nb_col)
			if ((line->index + lenp) % nb_col == 0 && line->index > 0)
				tputs(tgetstr("up", NULL), 1, ft_pchar);
		line->index = line->index - 1;
	}
	while (line->index > 0 && line->buff[line->index] == ' ')
		line->index = line->index + 1;
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->index + lenp) % nb_col), 1, ft_pchar);
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
