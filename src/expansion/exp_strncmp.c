/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_strncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 16:43:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/30 16:43:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				exp_strncmp(const char *s1, const char *s2, unsigned int n)
{
	char		*p1;
	char		*p2;

	p1 = (char *)s1;
	p2 = (char *)s2;
	while (*p1 && *p2 && n--)
		if (*p1++ != *p2++)
			break ;
	return (*p1 - *p2);
}
