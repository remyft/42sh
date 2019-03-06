/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 03:52:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/06 13:03:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"
	#include <stdio.h>
#include "struct.h"
#include "shell.h"
#include "libft.h"

int				expand_glob(t_exp *param, t_ret *ret)
{
	char	*ptr;
	t_line	*line;
	t_slst	*glob;

	(void)param;
	(void)ret;
	printf("glob: [%.*s]\n", (int)param->buff_len, param->buff + param->i);
	ptr = ft_strndup((char *)param->buff + param->i, (int)param->buff_len);
	line = get_struct();
	glob = deal_globing(ptr, line->tree[1]);
	(void)glob;
	param_addchar(param->buff[param->i], ret);
	return (ERR_UNHANDLED);
	return (ERR_NONE);
}
