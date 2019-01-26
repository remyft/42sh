/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_branch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:37:51 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 01:44:12 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "put.h"

static int	free_null(void *data)
{
	free(data);
	return (0);
}

static int	deal_upper(t_tree *upper, char *src, int *lenm, t_slct **select)
{
	if (!upper)
		return (1);
	while (upper->value != ft_toupper(*src))
		if (!(upper = ft_toupper(*src) < upper->value ? upper->left
					: upper->right))
			return (1);
	if (!(src[1]))
		*lenm = upper->max_len > *lenm ? upper->max_len : *lenm;
	*select = ft_memalloc(sizeof(t_slct));
	(*select)->mln = upper;
	if (*(src + 1) && !((*select)->down =
				select_branch(upper->tern_next, src + 1, lenm)))
		return (free_null(*select));
	return (1);
}

static int	deal_lower(t_tree *lower, char *src, int *lenm, t_slct **select)
{
	while (lower && lower->value != ft_tolower(*src))
		lower = ft_tolower(*src) < lower->value ? lower->left : lower->right;
	if (lower && !(src[1]))
		*lenm = lower->max_len > *lenm ? lower->max_len : *lenm;
	if (lower)
	{
		if (*select)
		{
			(*select)->next = ft_memalloc(sizeof(t_slct));
			(*select)->next->prev = *select;
			(*select)->next->mln = lower;
			if (*(src + 1) && !((*select)->next->down =
						select_branch(lower->tern_next, src + 1, lenm)))
				return (free_null(*select));
		}
		else
		{
			*select = ft_memalloc(sizeof(t_slct));
			(*select)->mln = lower;
			if (*(src + 1) && !((*select)->down) && !((*select)->down =
						select_branch(lower->tern_next, src + 1, lenm)))
				return (free_null(*select));
		}
	}
	return (1);
}

t_slct		*select_branch(t_tree *upper, char *src, int *lenm)
{
	t_slct	*select;
	t_tree	*lower;

	select = NULL;
	lower = upper;
	if (*src)
		if (!(deal_upper(upper, src, lenm, &select)))
			return (NULL);
	if (*src && ft_toupper(*src) != ft_tolower(*src))
		if (!(deal_lower(lower, src, lenm, &select)))
			return (NULL);
	return (select);
}
