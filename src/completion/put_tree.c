/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:34:09 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 12:55:59 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "put.h"
#include "21sh.h"

static void	get_new_file(t_tree *tern, t_cpl_e env, t_line *line)
{
	char	*chr;
	int		i;

	if (!*(ft_strrchr(line->curr->buff, ' ') + 1))
		stercat(line->curr->buff_tmp, env.bru, line->curr->buff);
	else if (!ft_occuc(ft_strrchr(line->curr->buff, ' '), '/'))
	{
		chr = ft_strrchr(line->curr->buff, ' ') + 1;
		i = 0;
		while (&(line->curr->buff)[i] != chr)
			i++;
		ft_strcpy(&(line->curr->buff)[i], env.bru);
	}
	else
	{
		chr = ft_strrchr(line->curr->buff, '/') + 1;
		i = 0;
		while (&(line->curr->buff)[i] != chr)
			i++;
		ft_strcpy(&(line->curr->buff)[i], env.bru);
	}
	ft_strncat(line->curr->buff, (char*)&(tern->value), 1);
}

static void	get_new_buff(t_tree *tern, t_cpl_e env, t_line *line)
{
	if (!tern->tput && *env.put && *(line->e_cmpl) & COMPLETION)
	{
		tputs(tgetstr("mr", NULL), 1, ft_pchar);
		tern->tput = 1;
		*env.put = 0;
		if (ft_occuc(line->curr->buff, ' '))
			get_new_file(tern, env, line);
		else
		{
			ft_bzero(line->curr->buff, ft_strlen(line->curr->buff));
			ft_strcpy(line->curr->buff, env.bru);
			ft_strncat(line->curr->buff, (char *)&(tern->value), 1);
		}
	}
	else
		tputs(tgetstr("me", NULL), 1, ft_pchar);
}

static void	put_space(t_cpl_e env, int *car_ret)
{
	if (*car_ret < env.nb_col - 1)
	{
		ft_putchars(' ', env.lenm - ft_strlen(env.bru) + 1);
		*car_ret += 1;
	}
	else
	{
		ft_putchars(' ', env.lenm - ft_strlen(env.bru) + 1);
		ft_putchar('\n');
		*car_ret = 0;
		*env.nb_ret += 1;
	}
}

void		ft_put_tree(t_tree *tern, t_cpl_e env, t_line *line, int *car_ret)
{
	if (tern->left)
		ft_put_tree(tern->left, env, line, car_ret);
	if (tern->tern_next && (tern->value != '.' || env.bru[0] == '.'
				|| env.lvl >= 1))
	{
		env.bru[env.lvl] = tern->value;
		env.lvl += 1;
		ft_put_tree(tern->tern_next, env, line, car_ret);
		env.lvl -= 1;
	}
	if (tern && !tern->tern_next)
	{
		env.bru[env.lvl] = '\0';
		get_new_buff(tern, env, line);
		ft_putstr(env.bru);
		put_space(env, car_ret);
	}
	if (tern->right)
		ft_put_tree(tern->right, env, line, car_ret);
}
