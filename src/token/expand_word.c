/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 04:02:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/23 02:07:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static size_t	my_strlen(const char *dst)
{
	if (!dst)
		return (0);
	return (ft_strlen(dst));
}

static char		*my_strcpy(char *dst, const char *src)
{
	if (!dst)
		return (NULL);
	return (ft_strcpy(dst, src));
}

static char		*my_strnjoin(char *dst, const char *src, size_t n)
{
	char		*ret;

	if (n == 0)
		return (dst);
	if (!(ret = ft_memalloc(my_strlen(dst) + n + 1)))
		return (dst);
	if (dst)
		my_strcpy(ret, dst);
	ft_strncat(ret, src, n);
	if (dst)
		free(dst);
	return (ret);
}

static char		*my_strnchr(const char *s, int c, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			return (char *)((s + i));
		i++;
	}
	return (NULL);
}

char			*expand_word(t_token *token)
{
	size_t		i;
	size_t		start;
	char		*ret;

	i = 0;
	start = i;
	ret = NULL;
	while (i < token->len)
	{
		if (token->head[i] == '\''
				&& (!token->quote || token->quote & SINGLE_QUOTE))
		{
			if (!my_strnchr(token->head + i + 1, '\'', token->len - i)
					&& !(token->quote & SINGLE_QUOTE))
			{
				i++;
				continue ;
			}
			ret = my_strnjoin(ret, token->head + start, i - start);
			start = i + 1;
			if (!token->quote)
				token->quote |= SINGLE_QUOTE;
			else
				token->quote &= ~SINGLE_QUOTE;
		}
		else if (token->head[i] == '"'
				&& (!token->quote || token->quote & DOUBLE_QUOTE))
		{
			if (!my_strnchr(token->head + i + 1, '"', token->len - i)
					&& !(token->quote & DOUBLE_QUOTE))
			{
				i++;
				continue ;
			}
			ret = my_strnjoin(ret, token->head + start, i - start);
			start = i + 1;
			if (!token->quote)
				token->quote |= DOUBLE_QUOTE;
			else
				token->quote &= ~DOUBLE_QUOTE;
		}
		else if (token->head[i] == '\\'
				&& (!token->quote || token->quote & DOUBLE_QUOTE))
		{
			ret = my_strnjoin(ret, token->head + start, i - start);
			start = i + 1;
			i++;
		}
		// else if (token->head[i] == '$' && !(token->quote & SINGLE_QUOTE))
		// {
		// 	ret = my_strnjoin(ret, token->head + start, i - start);
		// 	if (sub)
		// 	{
		// 		ret = my_strnjoin(ret, token->head + sub->head, sub->tail - sub->head);
		// 		start = sub->tail;
		// 		i = start - 1;
		// 		sub = sub->next;
		// 	}
		// }
		i++;
	}
	ret = my_strnjoin(ret, token->head + start, i - start);
	return (ret);
}
