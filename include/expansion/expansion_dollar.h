/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_dollar.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:18:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/05 16:29:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_DOLLAR_H
# define EXPANSION_DOLLAR_H

# include "expansion.h"

typedef struct	s_dollar
{
	int			(*check)(int);
	int			(*handler)(t_ret *, t_ret *, t_exp *);
}				t_dollar;

int				expand_dollar_do_expansion(t_ret *parameter);
int				expand_dollar_get_action(t_ret *parameter, t_exp *param);
int				expand_dollar_parameter(t_exp *param, t_ret *ret);
int				expand_dollar_parameter_value(t_ret *parameter, t_exp *param);
int				expand_dollar_special(t_ret *sub, t_ret *to, t_exp *param);
int				expand_dollar_subs(t_exp *param, t_ret *ret);
int				expand_dollar_word_value(t_ret *parameter, t_exp *param);
int				expand_dollar_word(t_ret *ret, t_exp *param, char op, char cl);

#endif
