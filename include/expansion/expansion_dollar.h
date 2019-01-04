/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_dollar.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:18:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 00:44:32 by gbourgeo         ###   ########.fr       */
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

#endif
