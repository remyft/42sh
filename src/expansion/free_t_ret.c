/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_ret.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 22:42:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/06 22:49:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void			free_t_ret(t_ret **ret)
{
	if ((*ret)->next)
		free_t_ret(&(*ret)->next);
	if ((*ret)->substitute)
		free((*ret)->substitute);
	free(*ret);
}
