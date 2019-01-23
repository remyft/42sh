/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:38:48 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/23 03:34:59 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	deal_complet(t_tree *file, t_line *line)
{
	int		put;
	size_t	j;
	int		nb_ret;

	put = 0;
	nb_ret = 0;
//	*(line->e_cmpl) |= COMPLETION;
	if (!line->curr->buff_tmp[8193])
	{
		ft_strcpy(line->curr->buff_tmp, line->curr->buff);
		line->curr->buff_tmp[8193] = 1;
	}
	else
		put = 1;
	if ((put = put_complet(line->curr->buff_tmp, file, line->curr->buff, &put, line, &nb_ret)) == 1)
		line->tmp[0] = 10;
	else if (put == -1)
	{
		*(line->e_cmpl) &= ~COMPLETION;
		line->is_putb = 0;
		line->tmp[0] = 0;
		return ;
	}
	while (nb_ret-- + 1)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(line->prompt)), 1, ft_pchar);
	j = -1;
	while (++j < line->len)
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
	ft_putstr(line->curr->buff);
	line->len = ft_strlen(line->curr->buff);
	line->index = line->len;
}

void		set_complet(t_line *line)
{
	DIR		*dir;

	dir = NULL;
	delete_down();
	*(line->e_cmpl) &= ~COMPLETION;
	line->is_putb = 0;
	line->tmp[0] = 0;
	if (ft_strrchr(line->curr->buff, ' ') && (dir = opendir(ft_strrchr(line->curr->buff, ' ') + 1)))
	{
		if (line->tree[2])
			free_tree(line->tree[2]);
		line->tree[2] = NULL;
		line->curr->buff[line->len] = '/';
		line->curr->buff[++(line->len)] = '\0';
		ft_putchar('/');
	}
	else
	{
		line->curr->buff[(line->len)] = ' ';
		line->curr->buff[++(line->len)] = '\0';
		ft_putchar(' ');
	}
	if (dir)
		closedir(dir);
	ft_bzero(line->curr->buff_tmp, 8194);
	line->index = line->len;
}

static int		inprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (ft_isprint(str[i]))
			return(1);
	return (0);
}

static t_tree	*set_tmp(char *buff)
{
	t_tree	*file;
	char	*stmp;

	stmp = ft_strrchr(buff, ' ') + 1;
	stmp = ft_strndup(stmp, ft_strrchr(stmp, '/') - stmp);
	file = create_file_tree(stmp, NULL);
	free(stmp);
	return (file);
}

int			str_chrglob(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '[' || str[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

void		get_complet(t_line *line)
{
	char	*ptr;
	t_slst	*tmp;
	int		i;
	static int j = 0;

	tmp = NULL;
	if (!inprint(line->curr->buff))
		return ;
	if ((ptr = ft_strrchr(line->curr->buff, ' ')) && str_chrglob(ptr))
		tmp = deal_globing(ptr + 1, line->tree[1]);
	else if (!ft_strchr(line->curr->buff, ' ') || !ft_strchr(ft_strrchr(line->curr->buff, ' '), '/'))
		deal_complet(!ft_strchr(line->curr->buff, ' ') ? line->tree[0] : line->tree[1], line);
	else
		if (line->tree[2] || (line->tree[2] = set_tmp(line->curr->buff)))
			deal_complet(line->tree[2], line);
	if (tmp)
	{
		while (tmp->prev)
			tmp = tmp->prev;
		ptr++;
		ft_bzero(ptr, ft_strlen(ptr));
		while (tmp)
		{
			i = -1;
			while (tmp->str[++i])
			{
				if (!ft_isalnum(tmp->str[i]) && tmp->str[i] != '/' && tmp->str[i] != '.' && tmp->str[i] != '_' && tmp->str[i] != '-')
					*ptr++ = '\\';
				*ptr = tmp->str[i];
				ptr++;
			}
			*ptr++ = ' ';
			j++;
			tmp = tmp->next;
		}
		i = line->len / line->nb_col;
		while (i--)
			tputs(tgetstr("up", NULL), 1, ft_pchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
		ft_putstr(line->curr->buff);
		line->len = ft_strlen(line->curr->buff);
		line->index = line->len;
	}
}
