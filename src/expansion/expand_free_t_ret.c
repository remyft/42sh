/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_free_t_ret.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 18:56:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/04 02:56:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void			expand_free_t_ret(t_ret *ret)
{
	if (ret->word)
		free(ret->word);
	ret->word = NULL;
	if (ret->substitute && ret->freeable)
		free(ret->substitute);
	ret->substitute = NULL;
}
