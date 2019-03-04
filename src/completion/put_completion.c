/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:42:34 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/04 17:28:34 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "put.h"
#include "shell_lib.h"
#include "shell_term.h"

static void	init_cpl(t_cpl_e *env, t_line *line, int *put, int *nb_ret)
{
	env->put = put;
	env->nb_ret = nb_ret;
	env->nb_col = line->nb_col / (env->lenm + 1);
	env->len = ft_strlen(env->chr);
/*	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	go_home(line);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);*/
}

void		deal_all_put(t_line *line, t_tree *tern, t_slct **select,
		t_cpl_e *env)
{
	int		psb;

	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	ft_putendl("");
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putendl("");
	psb = 1;
	env->put = &psb;
	env->nb_col = line->nb_col / (env->lenm + 1);
	env->len = ft_strlen(env->chr);
	deal_put(line, *env, *select, tern);
	if (*select)
		free_select(*select);
	if (env->chr)
		free(env->chr);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
}

int			check_put(t_line *line, t_tree *tern, t_slct **select,
		t_cpl_e *env)
{
	int		psb;

	psb = 0;
	if (!*select)
		get_tree_psb(tern, &psb);
	else
		get_psb(*select, ft_strlen(env->chr), 0, &psb);
	psb *= env->lenm;
	if (psb > (int)(line->nb_col * line->nb_line))
	{
		deal_all_put(line, tern, select, env);
		return (1);
	}
	return (0);
}

int			put_complet(t_tree *tern, int *put, t_line *line, int *nb_ret)
{
	t_slct	*select;
	t_cpl_e	env;
	int		ret;
	int		bsn;

	env.chr = NULL;
	bsn = 0;
	env.bru[0] = 0;
	select = NULL;
	env.nb_ret = nb_ret;
	if ((env.lenm = get_select(line, tern, &env, &select)) == -1)
		return (-1);
	init_cpl(&env, line, put, nb_ret);
	if ((env.lenm + ((line->len + line->lprompt) % line->nb_col) >=
			line->nb_col && *line->e_cmpl & COMPLETION))
	{
		bsn = 1;
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	}
	if ((ret = deal_put(line, env, select, tern)))
		return (ret);
	if (bsn)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	if (*line->e_cmpl & COMPLETION)
		if (line->is_putb < 1)
			line->is_putb += 1;
	*(line->e_cmpl) |= COMPLETION;
	if (env.chr)
		free(env.chr);
	if (select)
		free_select(select);
	return (0);
}
