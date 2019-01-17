/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_null_subst.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:59:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/16 01:06:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

int				word_null_subst(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)param;
	if (para->substitute && para->substitute[0])
		return (ERR_NONE);
	expand_free_t_ret(para, 0);
	ft_memcpy(para, subs, sizeof(*para));
	ft_memset(subs, 0, sizeof(*subs));
	return (ERR_NONE);
}
