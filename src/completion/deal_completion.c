/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:38:48 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 01:02:07 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	deal_complet(t_tree *file, t_line *line)
{
	int		put;
	int		j;

	*(line->e_cmpl) |= COMPLETION;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	if (!line->buff_tmp[8193])
	{
		ft_strcpy(line->buff_tmp, line->buff);
		line->buff_tmp[8193] = 1;
	}
	else
		put = 1;
	if ((put = put_complet(line->buff_tmp, file, line->buff, &put)) == 1)
		line->tmp[0] = 10;
	else if (put == -1)
	{
		*(line->e_cmpl) &= ~COMPLETION;
		line->tmp[0] = 0;
	}
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, ft_strlen(line->prompt) + 4), 1, ft_pchar);
	j = -1;
	while (++j < line->len)
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
	ft_putstr(line->buff);
	line->len = ft_strlen(line->buff);
	line->index = line->len;
}

void		set_complet(t_line *line)
{
	DIR		*dir;

	dir = NULL;
	delete_down();
	*(line->e_cmpl) &= ~COMPLETION;
	line->tmp[0] = 0;
	if (ft_strrchr(line->buff, ' ') && (dir = opendir(ft_strrchr(line->buff, ' ') + 1)))
	{
		if (line->tree[2])
			free_tree(line->tree[2]);
		line->tree[2] = NULL;
		line->buff[line->len] = '/';
		line->buff[++(line->len)] = '\0';
		ft_putchar('/');
	}
	else
	{
		line->buff[(line->len)] = ' ';
		line->buff[++(line->len)] = '\0';
		ft_putchar(' ');
	}
	if (dir)
		closedir(dir);
	ft_bzero(line->buff_tmp, 8194);
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
	file = create_file_tree(stmp);
	free(stmp);
	return (file);
}

void		get_complet(t_line *line)
{
	if (!inprint(line->buff))
		return ;
	if (!ft_strchr(line->buff, ' ') || !ft_strchr(ft_strrchr(line->buff, ' '), '/'))
		deal_complet(!ft_strchr(line->buff, ' ') ? line->tree[0] : line->tree[1], line);
	else
		if (line->tree[2] || (line->tree[2] = set_tmp(line->buff)))
			deal_complet(line->tree[2], line);
}
