/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tree_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:46:51 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 05:39:33 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

void	get_max_len(t_tree *curr, int *lenm)
{
	if (curr->left)
		get_max_len(curr->left, lenm);
	if (curr->right)
		get_max_len(curr->right, lenm);
	if (curr->max_len > *lenm)
		*lenm = curr->max_len;
}

void	get_put(t_tree *tern, int *ret, char c)
{
	if (tern->left)
		get_put(tern->left, ret, c);
	if (tern->right)
		get_put(tern->right, ret, c);
	if (tern->tern_next && (tern->value != '.' || c))
		get_put(tern->tern_next, ret, 1);
	if (tern && !tern->tern_next)
		if (tern->tput == 0)
			*ret = 1;
}

int		get_tstr(t_tree *tern, char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	while (tern)
	{
		str[i++] = tern->value;
		tern = tern->tern_next;
	}
	return (1);
}
