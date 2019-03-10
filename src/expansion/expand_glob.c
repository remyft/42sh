/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 03:52:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 14:09:09 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"
	#include <stdio.h>
#include "struct.h"
#include "shell.h"
#include "libft.h"
#include "put.h"

int		get_glob_len(t_slst *glob)
{
	int	len;

	len = 0;
	while (glob)
	{
		len += ft_strlen(glob->str) + 1;
		glob = glob->next;
	}
	return (len);
}

char	*get_glob_str(t_slst *glob)
{
	char	*str;
	int		i;
	int		j;

	if (!(str = ft_memalloc(sizeof(char) * get_glob_len(glob))))
		return (NULL);
	i = 0;
	while (glob)
	{
		j = -1;
		while (glob->str[++j])
			str[i++] = glob->str[j];
		if (glob->next)
			str[i++] = ' ';
		glob = glob->next;
	}
	return (str);
}

int				expand_glob(t_exp *param, t_ret *ret)
{
	char	*ptr;
	char	*tmp;
	t_line	*line;
	t_slst	*glob;

	(void)param;
	(void)ret;
	printf("ret: [%s]\n", ret->word);
	printf("glob: [%.*s]\n", (int)param->buff_len, param->buff + param->i);
	printf("len : [%d]\n", (int)param->buff_len);
	ptr = ft_strndup((char *)param->buff + param->i, (int)param->buff_len);
	tmp = ptr;
	if (ret->word != NULL)
		ptr = ft_strjoin(ret->word, ptr);
	ft_putendl(ptr);
	line = get_struct();
	if (GET_TREE(line->tree, TMP)
		|| (GET_TREE(line->tree, TMP) = set_tmp(ptr, 1)))
		glob = deal_globing(tmp, GET_TREE(line->tree, TMP));
	else
		glob = deal_globing(ptr, GET_TREE(line->tree, FILES));
	if (ptr != tmp)
		free(ptr);
	free(tmp);
	if (!glob)
	{
		return (ERR_NONE);
	}
//	ft_putendl("NEXT");
	while (glob->prev)
		glob = glob->prev;
	ptr = get_glob_str(glob);
	printf("str : [%s]\n", ptr);
	param_addchar(param->buff[param->i], ret);
	free(ptr);
	return (ERR_UNHANDLED);
	return (ERR_NONE);
}
