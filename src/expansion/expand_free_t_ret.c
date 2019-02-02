/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_free_t_ret.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 18:56:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/31 23:48:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include <stdio.h>
void			expand_free_t_ret(t_ret *ret, int free_ret)
{
	if (!ret)
		return ;
	// printf("RECURSIVE %d\n", free_ret);//
	expand_free_t_ret(ret->next, 1);
	// printf("word [%s]\n", ret->word);
	if (ret->word)
		free(ret->word);
	// printf("substitute [%s]\n", ret->substitute);
	if (ret->substitute && ret->freeable)
		free(ret->substitute);
	ft_memset(ret, 0, sizeof(*ret));
	if (free_ret)
		free(ret);
}
